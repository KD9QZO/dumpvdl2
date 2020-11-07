/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "PMCPDLCMessageSetVersion1"
 * 	found in "../../../dumpvdl2.asn1/atn-b1_cpdlc-v1.asn1"
 * 	`asn1c -fcompound-names -fincludes-quoted -gen-PER`
 */

#ifndef	_ReportedWaypointTime_H_
#define	_ReportedWaypointTime_H_


#include "asn_application.h"

/* Including external dependencies */
#include "Time.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ReportedWaypointTime */
typedef Time_t	 ReportedWaypointTime_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ReportedWaypointTime;
asn_struct_free_f ReportedWaypointTime_free;
asn_struct_print_f ReportedWaypointTime_print;
asn_constr_check_f ReportedWaypointTime_constraint;
ber_type_decoder_f ReportedWaypointTime_decode_ber;
der_type_encoder_f ReportedWaypointTime_encode_der;
xer_type_decoder_f ReportedWaypointTime_decode_xer;
xer_type_encoder_f ReportedWaypointTime_encode_xer;
per_type_decoder_f ReportedWaypointTime_decode_uper;
per_type_encoder_f ReportedWaypointTime_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _ReportedWaypointTime_H_ */
#include "asn_internal.h"