#include "x16rw-gate.h"

void x16rw_getAlgoString( const char* prevblock, char *output )
{
   char *sptr = output;
   uint8_t sumOfSeven = 0;
   for ( int j = 0; j < X16RW_HASH_FUNC_COUNT - 1; j++ )
   {
      uint8_t b = (15 - j) >> 1; // 16 first ascii hex chars (lsb in uint256)
      uint8_t algoDigit = (j & 1) ? prevblock[b] & 0xF : prevblock[b] >> 4;
      if (j > 7)
         sumOfSeven += algoDigit;
      if (algoDigit >= 10)
         sprintf(sptr, "%c", 'A' + (algoDigit - 10));
      else
         sprintf(sptr, "%u", (uint32_t) algoDigit);
      sptr++;
   }
   uint8_t algoDigit;
   if(sumOfSeven < 28)
      algoDigit = 0;
   else if(sumOfSeven < 39)
      algoDigit = 1;
   else if(sumOfSeven < 47)
      algoDigit = 2;
   else if(sumOfSeven < 54)
      algoDigit = 3;
   else if(sumOfSeven < 61)
      algoDigit = 4;
   else if(sumOfSeven < 66)
      algoDigit = 5;
   else if(sumOfSeven < 72)
      algoDigit = 6;
   else if(sumOfSeven < 76)
      algoDigit = 7;
   else if(sumOfSeven < 81)
      algoDigit = 8;
   else if(sumOfSeven < 86)
      algoDigit = 9;
   else if(sumOfSeven < 90)
      algoDigit = 10;
   else if(sumOfSeven < 94)
      algoDigit = 11;
   else if(sumOfSeven < 97)
      algoDigit = 12;
   else if(sumOfSeven < 100)
      algoDigit = 13;
   else if(sumOfSeven < 103)
      algoDigit = 14;
   else
      algoDigit = 15;
   if (algoDigit >= 10)
      sprintf(sptr, "%c", 'A' + (algoDigit - 10));
   else
      sprintf(sptr, "%u", (uint32_t) algoDigit);
   sptr++;

   *sptr = '\0';
}

void x16rws_getAlgoString( const char* prevblock, char *output )
{
   uint8_t* data = (uint8_t*)prevblock;
   strcpy( output, "0123456789ABCDEF" );
   for ( int i = 0; i < 16; i++ )
   {
      uint8_t b = (15 - i) >> 1; // 16 ascii hex chars, reversed
      uint8_t algoDigit = (i & 1) ? data[b] & 0xF : data[b] >> 4;
      int offset = algoDigit;
      // insert the nth character at the front
      char oldVal = output[offset];
      for( int j = offset; j-- > 0; )
         output[j+1] = output[j];
      output[0] = oldVal;
   }
}

bool register_x16rw_algo( algo_gate_t* gate )
{
#if defined (X16RW_4WAY)
  init_x16rw_4way_ctx();
  gate->scanhash  = (void*)&scanhash_x16rw_4way;
  gate->hash      = (void*)&x16rw_4way_hash;
#else
  init_x16rw_ctx();
  gate->scanhash  = (void*)&scanhash_x16rw;
  gate->hash      = (void*)&x16rw_hash;
#endif
  gate->optimizations = SSE2_OPT | AES_OPT | AVX2_OPT;
  gate->set_target = (void*)&alt_set_target;
  x16_rw_s_getAlgoString = (void*)&x16rw_getAlgoString;
  return true;
};

bool register_x16rws_algo( algo_gate_t* gate )
{
#if defined (X16RW_4WAY)
  init_x16rw_4way_ctx();
  gate->scanhash  = (void*)&scanhash_x16rw_4way;
  gate->hash      = (void*)&x16rw_4way_hash;
#else
  init_x16rw_ctx();
  gate->scanhash  = (void*)&scanhash_x16rw;
  gate->hash      = (void*)&x16rw_hash;
#endif
  gate->optimizations = SSE2_OPT | AES_OPT | AVX2_OPT;
  gate->set_target = (void*)&alt_set_target;
  x16_rw_s_getAlgoString = (void*)&x16rws_getAlgoString;
  return true;
};

