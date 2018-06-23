// This file has a few change (In order to incorporate in sstd by ADMIS_Walker)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  WjCryptLib_Sha1
//
//  Implementation of SHA1 hash function.
//  Original author:  Steve Reid <sreid@sea-to-sky.net>
//  Contributions by: James H. Brown <jbrown@burgoyne.com>, Saul Kravitz <Saul.Kravitz@celera.com>,
//  and Ralph Giles <giles@ghostscript.com>
//  Modified by WaterJuice retaining Public Domain license.
//
//  This is free and unencumbered software released into the public domain - June 2013 waterjuice.org
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../typeDef.h"
#include <stdint.h>
#include <stdio.h>

struct sha1_state{
    uint32        State[5];
    uint32        Count[2];
    uint8         Buffer[64];
};

#define SHA1_HASH_SIZE ( 160 / 8 )

void sha_init(sha1_state& md);
void sha_process(sha1_state& md, void const* Buffer, uint32 BufferSize);
void sha_done(sha1_state& md, unsigned char* Digest);

void Sha1Calculate(void const* Buffer, uint32_t BufferSize, unsigned char* Digest);

