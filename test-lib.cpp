#include <jni.h>
#include <string>
#include <sys/time.h>
#include <arm_neon.h>
#include "AES.h"


#define Nb 4
#define Nr 10

/*****************************************************************************/
const unsigned char input[16] = { /* user input, unaligned buffer */
		0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0xf4
	};	
const unsigned char key01[16] = { /* user input, unaligned buffer */
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	};
const unsigned char key[16] = { /* user input, unaligned buffer */
		0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x9 , 0xcf, 0x4f, 0x3c
	};
const unsigned char subkeys[10][16] = { /* library controlled, aligned buffer */
		{0xA0, 0xFA, 0xFE, 0x17, 0x88, 0x54, 0x2c, 0xb1, 0x23, 0xa3, 0x39, 0x39, 0x2a, 0x6c, 0x76, 0x05},
		{0xF2, 0xC2, 0x95, 0xF2, 0x7a, 0x96, 0xb9, 0x43, 0x59, 0x35, 0x80, 0x7a, 0x73, 0x59, 0xf6, 0x7f},
		{0x3D, 0x80, 0x47, 0x7D, 0x47, 0x16, 0xFE, 0x3E, 0x1E, 0x23, 0x7E, 0x44, 0x6D, 0x7A, 0x88, 0x3B},
		{0xEF, 0x44, 0xA5, 0x41, 0xA8, 0x52, 0x5B, 0x7F, 0xB6, 0x71, 0x25, 0x3B, 0xDB, 0x0B, 0xAD, 0x00},
		{0xD4, 0xD1, 0xC6, 0xF8, 0x7C, 0x83, 0x9D, 0x87, 0xCA, 0xF2, 0xB8, 0xBC, 0x11, 0xF9, 0x15, 0xBC},
		{0x6D, 0x88, 0xA3, 0x7A, 0x11, 0x0B, 0x3E, 0xFD, 0xDB, 0xF9, 0x86, 0x41, 0xCA, 0x00, 0x93, 0xFD},
		{0x4E, 0x54, 0xF7, 0x0E, 0x5F, 0x5F, 0xC9, 0xF3, 0x84, 0xA6, 0x4F, 0xB2, 0x4E, 0xA6, 0xDC, 0x4F},
		{0xEA, 0xD2, 0x73, 0x21, 0xB5, 0x8D, 0xBA, 0xD2, 0x31, 0x2B, 0xF5, 0x60, 0x7F, 0x8D, 0x29, 0x2F},
		{0xAC, 0x77, 0x66, 0xF3, 0x19, 0xFA, 0xDC, 0x21, 0x28, 0xD1, 0x29, 0x41, 0x57, 0x5c, 0x00, 0x6E},
		{0xD0, 0x14, 0xF9, 0xA8, 0xC9, 0xEE, 0x25, 0x89, 0xE1, 0x3F, 0x0c, 0xC8, 0xB6, 0x63, 0x0C, 0xA6}
	};
const unsigned char key00[16]= { /* user input, unaligned buffer */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 , 0x00, 0x00, 0x00
	};




	
uint8x16_t aes10round_encode(const unsigned char *pinput,const unsigned char * pkey){
		
	uint8x16_t block;
	const unsigned char * psubkeys=(const unsigned char *)subkeys;
	block = vld1q_u8(pinput);
	// AES single round encryption(1)
	block = vaeseq_u8(block, vld1q_u8(pkey));
	// AES mix columns(1)
	block = vaesmcq_u8(block);

	// AES single round encryption(2)
	block = vaeseq_u8(block, vld1q_u8(psubkeys));
	// AES mix columns(2)
	block = vaesmcq_u8(block);

	// AES single round encryption(3)
	block = vaeseq_u8(block, vld1q_u8(psubkeys+1*16));
	// AES mix columns(3)
	block = vaesmcq_u8(block);
 
	// AES single round encryption(4)
	block = vaeseq_u8(block, vld1q_u8(psubkeys+2*16));
	// AES mix columns(4)
	block = vaesmcq_u8(block);

	// AES single round encryption(5)
	block = vaeseq_u8(block, vld1q_u8(psubkeys+3*16));
	// AES mix columns(5)
	block = vaesmcq_u8(block);

	// AES single round encryption(6)
	block = vaeseq_u8(block, vld1q_u8(psubkeys+4*16));
	// AES mix columns(6)
	block = vaesmcq_u8(block);

	// AES single round encryption(7)
	block = vaeseq_u8(block, vld1q_u8(psubkeys+5*16));
	// AES mix columns(7)
	block = vaesmcq_u8(block);

	// AES single round encryption(8)
	block = vaeseq_u8(block, vld1q_u8(psubkeys+6*16));
	// AES mix columns(8)
	block = vaesmcq_u8(block);

	// AES single round encryption(9)
	block = vaeseq_u8(block, vld1q_u8(psubkeys+7*16));
	// AES mix columns(9)
	block = vaesmcq_u8(block);

	// AES single round encryption(10)
	block = vaeseq_u8(block, vld1q_u8(psubkeys+8*16));
	
	// Final Add (bitwise Xor)
	block = veorq_u8(block, vld1q_u8(psubkeys+9*16));
	
	return block;
}

uint8x16_t aes10round_decode(uint8x16_t pinput,const unsigned char * pkey){
	uint8x16_t block=pinput;
	uint8x16_t keyfor00;
	keyfor00=vld1q_u8((const unsigned char *)key00);
	const unsigned char * psubkeys=(const unsigned char *)subkeys;
	// AES single round decryption(1)
	block = vaesdq_u8(block, vld1q_u8(psubkeys+9*16));
	block = veorq_u8(block, vld1q_u8(psubkeys+8*16));
	// AES mix columns(1)
	block = vaesimcq_u8(block);
	// AES single round decryption(2)
	block = vaesdq_u8(block, keyfor00);
	block = veorq_u8(block, vld1q_u8(psubkeys+7*16));
	// AES mix columns(2)
	block = vaesimcq_u8(block);
	// AES single round decryption(3)
	block = vaesdq_u8(block, keyfor00);
	block = veorq_u8(block, vld1q_u8(psubkeys+6*16));
	// AES mix columns(3)
	block = vaesimcq_u8(block);
	// AES single round decryption(4)
	block = vaesdq_u8(block, keyfor00);
	block = veorq_u8(block, vld1q_u8(psubkeys+5*16));
	// AES mix columns(4)
	block = vaesimcq_u8(block);
	// AES single round decryption(5)
	block = vaesdq_u8(block, keyfor00);
	block = veorq_u8(block, vld1q_u8(psubkeys+4*16));
	// AES mix columns(5)
	block = vaesimcq_u8(block);
	// AES single round decryption(6)
	block = vaesdq_u8(block, keyfor00);
	block = veorq_u8(block, vld1q_u8(psubkeys+3*16));
	// AES mix columns(6)
	block = vaesimcq_u8(block);
	// AES single round decryption(7)
	block = vaesdq_u8(block, keyfor00);
	block = veorq_u8(block, vld1q_u8(psubkeys+2*16));
	// AES mix columns(7)
	block = vaesimcq_u8(block);
	// AES single round decryption(8)
	block = vaesdq_u8(block, keyfor00);
	block = veorq_u8(block, vld1q_u8(psubkeys+1*16));
	// AES mix columns(8)
	block = vaesimcq_u8(block);
	// AES single round decryption(9)
	block = vaesdq_u8(block, keyfor00);
	block = veorq_u8(block, vld1q_u8(psubkeys+0*16));
	// AES mix columns(9)
	block = vaesimcq_u8(block);
	// AES single round decryption(10)
	block = vaesdq_u8(block, keyfor00);
	block = veorq_u8(block, vld1q_u8(key));
	
	return block;
}

/*****************************************************************************/
JNIEXPORT jlong JNICALL Java_com_example_arm_AES_AESARM
  (JNIEnv *env, jobject jthis, jbyteArray jby, jint testround,jint timescale){
  
	//timeval starttime,endtime;
	//struct timespec time_start={0,0},time_end={0,0};
	const unsigned char * pinput=input;
	const unsigned char * pkey=key;
	
	unsigned char output[16]={0x00};
	//get starttime
	long starttime;
	long endtime;
	//gettimeofday(&starttime,0);
	//clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time_start);
	uint8x16_t block;
for(int i=0;i<testround;i++){
	if(i==0){
		starttime=clock();
	}
	//block = vld1q_u8(pinput);
	//block = vaeseq_u8(block,vld1q_u8(pkey));
	//block = vaesdq_u8(block,vld1q_u8(pkey));
	block=aes10round_encode(pinput,pkey);
	//vst1q_u8((unsigned char *)input01, block);
	block=aes10round_decode(block,pkey);
	if(i==testround-1){
		vst1q_u8((unsigned char *)output, block);
		endtime=clock();
	}
}
	

	//get endtime
	
	//gettimeofday(&endtime,0);
	//if(i==testround){
	//	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time_end);
	//}		
	pinput=NULL;
	pkey=NULL;
	//psubkeys=NULL;
	//double timeuse = 1000000*(endtime.tv_sec - starttime.tv_sec) + endtime.tv_usec - starttime.tv_usec;
	//timeuse /=timescale;
	//long long TIME=time_end.tv_nsec-time_start.tv_nsec;
	//除以1000则进行毫秒计时，如果除以1000000则进行秒级别计时，如果除以1则进行微妙级别计时
	env->SetByteArrayRegion(jby,0,16,(const jbyte*)output);

//return timeuse;
return endtime-starttime;
}


/*****************************************************************************/
typedef uint8_t state_t[4][4];

const state_t uint8input={ /* user input, unaligned buffer */
		0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0xf4
	};
const uint8_t RoundKey[11][16]={ /* library controlled, aligned buffer */
		{0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x9 , 0xcf, 0x4f, 0x3c},
		{0xA0, 0xFA, 0xFE, 0x17, 0x88, 0x54, 0x2c, 0xb1, 0x23, 0xa3, 0x39, 0x39, 0x2a, 0x6c, 0x76, 0x05},
		{0xF2, 0xC2, 0x95, 0xF2, 0x7a, 0x96, 0xb9, 0x43, 0x59, 0x35, 0x80, 0x7a, 0x73, 0x59, 0xf6, 0x7f},
		{0x3D, 0x80, 0x47, 0x7D, 0x47, 0x16, 0xFE, 0x3E, 0x1E, 0x23, 0x7E, 0x44, 0x6D, 0x7A, 0x88, 0x3B},
		{0xEF, 0x44, 0xA5, 0x41, 0xA8, 0x52, 0x5B, 0x7F, 0xB6, 0x71, 0x25, 0x3B, 0xDB, 0x0B, 0xAD, 0x00},
		{0xD4, 0xD1, 0xC6, 0xF8, 0x7C, 0x83, 0x9D, 0x87, 0xCA, 0xF2, 0xB8, 0xBC, 0x11, 0xF9, 0x15, 0xBC},
		{0x6D, 0x88, 0xA3, 0x7A, 0x11, 0x0B, 0x3E, 0xFD, 0xDB, 0xF9, 0x86, 0x41, 0xCA, 0x00, 0x93, 0xFD},
		{0x4E, 0x54, 0xF7, 0x0E, 0x5F, 0x5F, 0xC9, 0xF3, 0x84, 0xA6, 0x4F, 0xB2, 0x4E, 0xA6, 0xDC, 0x4F},
		{0xEA, 0xD2, 0x73, 0x21, 0xB5, 0x8D, 0xBA, 0xD2, 0x31, 0x2B, 0xF5, 0x60, 0x7F, 0x8D, 0x29, 0x2F},
		{0xAC, 0x77, 0x66, 0xF3, 0x19, 0xFA, 0xDC, 0x21, 0x28, 0xD1, 0x29, 0x41, 0x57, 0x5c, 0x00, 0x6E},
		{0xD0, 0x14, 0xF9, 0xA8, 0xC9, 0xEE, 0x25, 0x89, 0xE1, 0x3F, 0x0c, 0xC8, 0xB6, 0x63, 0x0C, 0xA6}
	};

// The lookup-tables are marked const so they can be placed in read-only storage instead of RAM
// The numbers below can be computed dynamically trading ROM for RAM - 
// This can be useful in (embedded) bootloader applications, where ROM is often limited.
static const uint8_t sbox[256] = {
  //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };


#define getSBoxValue(num) (sbox[(num)])

// This function adds the round key to state.
// The round key is added to the state by an XOR function.
static void AddRoundKey(uint8_t round, state_t* state, const uint8_t* RoundKey)
{
  uint8_t i,j;
  for (i = 0; i < 4; ++i)
  {
    for (j = 0; j < 4; ++j)
    {
      (*state)[i][j] ^= RoundKey[(round * Nb * 4) + (i * Nb) + j];
    }
  }
}

// The SubBytes Function Substitutes the values in the
// state matrix with values in an S-box.
static void SubBytes(state_t* state)
{
  uint8_t i, j;
  for (i = 0; i < 4; ++i)
  {
    for (j = 0; j < 4; ++j)
    {
      (*state)[j][i] = getSBoxValue((*state)[j][i]);
    }
  }
}
// The ShiftRows() function shifts the rows in the state to the left.
// Each row is shifted with different offset.
// Offset = Row number. So the first row is not shifted.
static void ShiftRows(state_t* state)
{
  uint8_t temp;

  // Rotate first row 1 columns to left  
  temp           = (*state)[0][1];
  (*state)[0][1] = (*state)[1][1];
  (*state)[1][1] = (*state)[2][1];
  (*state)[2][1] = (*state)[3][1];
  (*state)[3][1] = temp;

  // Rotate second row 2 columns to left  
  temp           = (*state)[0][2];
  (*state)[0][2] = (*state)[2][2];
  (*state)[2][2] = temp;

  temp           = (*state)[1][2];
  (*state)[1][2] = (*state)[3][2];
  (*state)[3][2] = temp;

  // Rotate third row 3 columns to left
  temp           = (*state)[0][3];
  (*state)[0][3] = (*state)[3][3];
  (*state)[3][3] = (*state)[2][3];
  (*state)[2][3] = (*state)[1][3];
  (*state)[1][3] = temp;
}

static uint8_t xtime(uint8_t x)
{
  return ((x<<1) ^ (((x>>7) & 1) * 0x1b));
}

// MixColumns function mixes the columns of the state matrix
static void MixColumns(state_t* state)
{
  uint8_t i;
  uint8_t Tmp, Tm, t;
  for (i = 0; i < 4; ++i)
  {  
    t   = (*state)[i][0];
    Tmp = (*state)[i][0] ^ (*state)[i][1] ^ (*state)[i][2] ^ (*state)[i][3] ;
    Tm  = (*state)[i][0] ^ (*state)[i][1] ; Tm = xtime(Tm);  (*state)[i][0] ^= Tm ^ Tmp ;
    Tm  = (*state)[i][1] ^ (*state)[i][2] ; Tm = xtime(Tm);  (*state)[i][1] ^= Tm ^ Tmp ;
    Tm  = (*state)[i][2] ^ (*state)[i][3] ; Tm = xtime(Tm);  (*state)[i][2] ^= Tm ^ Tmp ;
    Tm  = (*state)[i][3] ^ t ;              Tm = xtime(Tm);  (*state)[i][3] ^= Tm ^ Tmp ;
  }
}
/*****************************************************************************/

JNIEXPORT jlong JNICALL Java_com_example_arm_AES_AESNORMAL
  (JNIEnv *env, jobject jthis, jbyteArray jby, jint testround,jint timescale){  
	//timeval starttime,endtime;
	struct timespec time_start={0,0},time_end={0,0};
	state_t state;
	state_t *pstate=(state_t *)state;
	uint8_t round = 0;
	int i;
	//get starttime
	long starttime;
	long endtime;
	//gettimeofday(&starttime,0);
	//clock_gettime(CLOCK_REALTIME,&time_start);
	  for(i=0;i<testround;i++){
		
		if(i==0){
		starttime=clock();
	}
		
		round = 0;
		
		for (int j = 0; j < 4; ++j){
			for (int z = 0; z < 4; ++z){
					(*pstate)[j][z] = uint8input[j][z];
			}
		}

		 
		// Add the First round key to the state before starting the rounds.
		AddRoundKey(0, pstate, (const uint8_t*)RoundKey);
		for (round = 1; ; ++round){
			SubBytes(pstate);
			ShiftRows(pstate);
			if (round == Nr) {
			break;
			}
			MixColumns(pstate);
			AddRoundKey(round, pstate, (const uint8_t*)RoundKey);
		}
		// Add round key to last round
		AddRoundKey(Nr, pstate, (const uint8_t*)RoundKey);
		if(i==testround-1){
			endtime=clock();	
		}
	}
	//gettimeofday(&endtime,0);

	//if(i==testround){
	//	clock_gettime(CLOCK_REALTIME,&time_end);
	//}	
	
	//long long TIME=time_end.tv_nsec-time_start.tv_nsec;
	//double timeuse = 1000000*(endtime.tv_sec - starttime.tv_sec) + endtime.tv_usec - starttime.tv_usec;
	//timeuse /=timescale;
	//除以1000则进行毫秒计时，如果除以1000000则进行秒级别计时，如果除以1则进行微妙级别计时	  
	env->SetByteArrayRegion(jby,0,16,(const jbyte*)state);
//return timeuse;		  
return endtime-starttime;	  
  }

