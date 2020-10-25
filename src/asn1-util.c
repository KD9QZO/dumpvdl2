/*
 *  This file is a part of dumpvdl2
 *
 *  Copyright (c) 2017-2020 Tomasz Lemiech <szpajder@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <search.h>                 // lfind()
#include <libacars/vstring.h>       // la_vstring
#include <libacars/json.h>
#include "asn1/asn_application.h"   // asn_TYPE_descriptor_t
#include "dumpvdl2.h"               // debug_print(D_PROTO, )
#include "asn1-util.h"              // asn_formatter_table

static int compare_fmtr(void const *k, void const *m) {
	asn_formatter_t const *memb = m;
	return(k == memb->type ? 0 : 1);
}

int asn1_decode_as(asn_TYPE_descriptor_t *td, void **struct_ptr, uint8_t *buf, int size) {
	asn_dec_rval_t rval;
	rval = uper_decode_complete(0, td, struct_ptr, buf, size);
	if(rval.code != RC_OK) {
		debug_print(D_PROTO, "uper_decode_complete failed: %d\n", rval.code);
		return -1;
	}
	if(rval.consumed < (size_t)size) {
		debug_print(D_PROTO, "uper_decode_complete left %zd unparsed octets\n",
				(size_t)size - rval.consumed);
		return (int)((size_t)size - rval.consumed);
	}
#ifdef DEBUG
	if(Config.debug_filter & D_PROTO_DETAIL) {
		asn_fprint(stderr, td, *struct_ptr, 1);
	}
#endif
	return 0;
}

void asn1_output(asn1_formatter_param_t p, asn_formatter_t const *asn1_formatter_table,
		size_t asn1_formatter_table_len, bool dump_unknown_types) {
	if(p.td == NULL || p.sptr == NULL) return;
	asn_formatter_t *formatter = lfind(p.td, asn1_formatter_table, &asn1_formatter_table_len,
			sizeof(asn_formatter_t), compare_fmtr);
	if(formatter != NULL) {
		// NULL formatting routine is allowed - it means the type should be silently omitted
		if(formatter->format != NULL) {
			p.label = formatter->label;
			(*formatter->format)(p);
		}
	} else if(dump_unknown_types) {
		LA_ISPRINTF(p.vstr, p.indent, "-- Formatter for type %s not found, ASN.1 dump follows:\n", p.td->name);
		LA_ISPRINTF(p.vstr, p.indent, "%s", "");    // asn_sprintf does not indent the first line
		asn_sprintf(p.vstr, p.td, p.sptr, p.indent+1);
		EOL(p.vstr);
		LA_ISPRINTF(p.vstr, p.indent, "%s", "-- ASN.1 dump end\n");
	}
}

// text formatter for la_proto_nodes containing asn1_pdu_t data
void asn1_pdu_format_text(la_vstring *vstr, void const *data, int indent) {
	ASSERT(vstr != NULL);
	ASSERT(data);
	ASSERT(indent >= 0);

	asn1_pdu_t const *pdu = data;
	if(pdu->type == NULL) {   // No user data in APDU, so no decoding was attempted
		return;
	}
	if(pdu->data == NULL) {
		LA_ISPRINTF(vstr, indent, "%s: <empty PDU>\n", pdu->type->name);
		return;
	}
	if(Config.dump_asn1 == true) {
		LA_ISPRINTF(vstr, indent, "ASN.1 dump:\n");
		// asn_fprint does not indent the first line
		LA_ISPRINTF(vstr, indent + 1, "");
		asn_sprintf(vstr, pdu->type, pdu->data, indent + 2);
		EOL(vstr);
	}
	ASSERT(pdu->formatter_table_text != NULL);
	asn1_output((asn1_formatter_param_t){
		.vstr = vstr,
		.td = pdu->type,
		.sptr = pdu->data,
		.indent = indent
		},
		pdu->formatter_table_text, pdu->formatter_table_text_len, true);
}

void asn1_pdu_format_json(la_vstring *vstr, void const *data) {
	ASSERT(vstr != NULL);
	ASSERT(data);

	asn1_pdu_t const *pdu = data;
	if(pdu->type == NULL) {     // No user data in APDU - no decoding was attempted
		return;
	}
	if(pdu->data == NULL) {     // Empty PDU
		return;
	}
	ASSERT(pdu->formatter_table_json != NULL);
	asn1_output((asn1_formatter_param_t){
		.vstr = vstr,
		.td = pdu->type,
		.sptr = pdu->data,
		},
		pdu->formatter_table_json, pdu->formatter_table_json_len, false);
}

// a destructor for la_proto_nodes containing asn1_pdu_t data
void asn1_pdu_destroy(void *data) {
	if(data == NULL) {
		return;
	}
	asn1_pdu_t *pdu = data;
	if(pdu->type != NULL) {
		pdu->type->free_struct(pdu->type, pdu->data, 0);
	}
	XFREE(data);
}
