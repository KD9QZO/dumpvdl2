/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "PMCPDLCMessageSetVersion1"
 * 	found in "../../../dumpvdl2.asn1/atn-b1_cpdlc-v1.asn1"
 * 	`asn1c -fcompound-names -fincludes-quoted -gen-PER`
 */

#ifndef	_TimeETAatDest_H_
#define	_TimeETAatDest_H_


#include "asn_application.h"

/* Including external dependencies */
#include "Time.h"

#ifdef __cplusplus
extern "C" {
#endif

/* TimeETAatDest */
typedef Time_t	 TimeETAatDest_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TimeETAatDest;
asn_struct_free_f TimeETAatDest_free;
asn_struct_print_f TimeETAatDest_print;
asn_constr_check_f TimeETAatDest_constraint;
ber_type_decoder_f TimeETAatDest_decode_ber;
der_type_encoder_f TimeETAatDest_encode_der;
xer_type_decoder_f TimeETAatDest_decode_xer;
xer_type_encoder_f TimeETAatDest_encode_xer;
per_type_decoder_f TimeETAatDest_decode_uper;
per_type_encoder_f TimeETAatDest_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _TimeETAatDest_H_ */
#include "asn_internal.h"