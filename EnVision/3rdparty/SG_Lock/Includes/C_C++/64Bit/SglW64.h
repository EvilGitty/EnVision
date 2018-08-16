/****************************************************************************
 SGLW64.H / 11.2010 / MS-WINDOWS 64-Bit (XP/VISTA/7)

 2010 (C) SG Intec Ltd & Co KG

*******************************************************************************/


#define SGL_SUCCESS                         0x0000
#define SGL_DGL_NOT_FOUND                   0x0001
#define SGL_LPT_BUSY                        0x0002
#define SGL_LPT_OPEN_ERROR                  0x0003
#define SGL_NO_LPT_PORT_FOUND               0x0004
#define SGL_AUTHENTICATION_REQUIRED         0x0005
#define SGL_AUTHENTICATION_FAILED           0x0006
#define SGL_FUNCTION_NOT_SUPPORTED          0x0007
#define SGL_PARAMETER_INVALID				0x0008
#define SGL_SIGNATURE_INVALID				0x0009
#define SGL_USB_BUSY				        0x000A



#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************/
/*                                                                 */
/*  SG-Lock API basic functions (supported by all SG-Lock moduls)  */
/*                                                                 */
/*******************************************************************/
	
unsigned  int
SglAuthent(
  unsigned  int *AuthentCode );
	
unsigned  int __fastcall
SglSearchLock(
   unsigned  int ProductId);             // The ProductId value programmed
                                             // of all moduls is "1". Change it
					     // to your needs!
unsigned  int __fastcall
SglReadSerialNumber(
   unsigned  int ProductId,
   unsigned  int *SerialNumber);         // pointer to 1 DWORD, read only!

// administration functions
unsigned  int __fastcall
SglReadProductId(
   unsigned  int *ProductIdPtr);         // pointer to 1 DWORD
    
unsigned  int __fastcall
SglWriteProductId(
   unsigned  int OldProductId,
   unsigned  int NewProductId);

/*******************************************************************/
/*                                                                 */
/*  SG-Lock API extended functions (supported only by L3,L4,U3,U4) */
/*                                                                 */
/*******************************************************************/

// Memory functions
unsigned  int __fastcall
SglReadData(
   unsigned  int ProductId,
   unsigned  int Address,         // L3,U3: 0-63; L4,U4: 0-255
   unsigned  int Count,           // L3,U3: 1-63; L4,U4: 1-255
   unsigned  int *Data);          // data array with minimum size 
                                      // of requested data  

unsigned  int __fastcall
SglWriteData(
   unsigned  int ProductId,
   unsigned  int Address,         // L3,U3: 0-63; L4,U4: 0-255
   unsigned  int Count,           // L3,U3: 1-63; L4,U4: 1-255
   unsigned  int *Data);          // data array with minimum size
                                      // of requested data  

// Counter functions
unsigned  int __fastcall
SglReadCounter(
   unsigned  int ProductId,
   unsigned  int CntNum,          // number of counter: L3,U3: 0-15
   unsigned  int *Data);          // L4,U4: 0-63, *Data is a pointer to 1 DWORD

unsigned  int __fastcall
SglWriteCounter(
   unsigned  int ProductId,
   unsigned  int CntNum,          // number of counter: L3,U3: 0-15
   unsigned  int Data);           // L4,U4: 0-63, Data is the counter value

// Cryptographic and signing functions
unsigned  int __fastcall
SglCryptLock(
   unsigned  int ProductId,
   unsigned  int KeyNum,          // number of key: L2, U2: 0 ; L3,U3: 0-1 ; L4,U4: 0-15
   unsigned  int CryptMode,       // 0=encrypt, 1=decrypt
   unsigned  int BlockCnt,        // number of 8-Bytes blocks to proccess
   unsigned  int *Data);          // data to process, size must be BlockCnt * 8 Bytes

// Values valid for parameter MODE of Sign functions
#define SGL_SIGNATURE_GENERATE 			0
#define SGL_SIGNATURE_VERIFY 			1

unsigned  int
SglSignData( 
	unsigned  int ProductId,
	unsigned  int *AppSignKey,
	unsigned  int LockSignKeyNum,
	unsigned  int Mode,
	unsigned  int LockSignInterval,
	unsigned  int DataLen,
	unsigned  int *Data,
	unsigned  int *Signature);


unsigned  int
SglSignDataApp( 
	unsigned  int *AppSignKey,
	unsigned  int Mode,
	unsigned  int DataLen,
	unsigned  int *Data,
	unsigned  int *Signature);

unsigned  int
SglSignDataLock( 
	unsigned  int  ProductId,
	unsigned  int  LockSignKeyNum,
	unsigned  int  Mode,
	unsigned  int  DataLen,
	unsigned  int  *Data,
	unsigned  int  *Signature);

unsigned  int
SglSignDataComb( 
	unsigned  int ProductId,
	unsigned  int *AppSignKey,
	unsigned  int LockSignKeyNum,
	unsigned  int Mode,
	unsigned  int LockSignInterval,
	unsigned  int DataLen,
	unsigned  int *Data,
	unsigned  int *Signature);



// Administrativ functions
unsigned  int __fastcall
SglWriteKey(
   unsigned  int ProductId,       // L2,U2: Key fixed - that means not writeable
   unsigned  int KeyNum,          // number of key: L3,U3: 0-1 ; L4,U4: 0-15 
   unsigned  int *Key);           // 128-Bit (16 Bytes) Key, write only!!! 

unsigned  int __fastcall
SglReadConfig(
   unsigned  int ProductId,
   unsigned  int Category,		// see below
   unsigned  int *Data);		// has to be an array of 8 DWord/32bit values 


// possible parameters for 'Category'
#define SGL_READ_CONFIG_LOCK_INFO			0x0000    // version of dongle hardware

// possible returns    
// Data[0] = ModelId ( see below )
#define SGL_CONFIG_LOCK_SERIES_2			0x0001
#define SGL_CONFIG_LOCK_SERIES_3			0x0002
#define SGL_CONFIG_LOCK_SERIES_4			0x0003
   
// Data[1] = Interface ( see below )  
#define SGL_CONFIG_INTERFACE_USB			0x0000
#define SGL_CONFIG_INTERFACE_LPT			0x0001

// Data[2] = Software Version of SG-Lock ( high word = major version, low word = minor version )
// Data[3] = Hardware Version of SG-Lock ( high word = major version, low word = minor version ) 
// Data[4] = Serial Number
// Data[5] = Memory Size ( size of memory in DWords !!)
// Data[6] = Counter Count
// Data[7] = 128 bit Key Count

/*******************************************************************/
/*                                                                 */
/*           End of SG-Lock API functions                          */
/*                                                                 */
/*******************************************************************/

/*******************************************************************/
/* helping functions that have to be included, but should not be   */
/* called directly from SG-Lock using application                  */
/*******************************************************************/

unsigned  int __fastcall
SglAuthentA(
  unsigned int *AuthentCode,
  unsigned int *AppRandNum,
  unsigned int *LibRandNum );

unsigned  int __fastcall
SglAuthentB(
  unsigned  int   *LibRandNum );


void SglTeaEncipher(
    const unsigned int *const   InData,
    unsigned int *const         OutData,
    const unsigned int * const  Key);



void SglTeaDecipher(
    const unsigned int *const   InData,
    unsigned int *const         OutData,
    const unsigned int * const  Key);









unsigned  int
SglAuthent(
  unsigned int *AuthentCode ) {

  
  unsigned int RandNum[2];
  unsigned int AppRandNum[2];
  unsigned int LibRandNum[2];
  unsigned int AuthentCodeLocal[8];
  unsigned int RetCode;
  unsigned int i;

  
  for( i=0; i<8; i++ ) {
    AuthentCodeLocal[i] = AuthentCode[i];
    AuthentCode[i]= (rand()<<16) | rand();
  }
  
  srand(AuthentCode[0]);
  RandNum[0] = (rand()<<16) | rand();
  RandNum[1] = (rand()<<16) | rand();

  AppRandNum[0] = RandNum[0];
  AppRandNum[1] = RandNum[1];
  
  RetCode = SglAuthentA(
	      AuthentCodeLocal,
	      AppRandNum,
	      LibRandNum);

  for( i=0; i<8; i++ ) {
    AuthentCode[i] = AuthentCodeLocal[i];
  }

  if( RetCode != SGL_SUCCESS ) {
      return SGL_AUTHENTICATION_FAILED;
  }  
  
  SglTeaEncipher( RandNum, RandNum, &AuthentCode[8] );

  if( (RandNum[0] != AppRandNum[0] ) || 
      (RandNum[1] != AppRandNum[1] ) ) {

      return SGL_AUTHENTICATION_FAILED;
      
  }

  SglTeaEncipher( LibRandNum, LibRandNum, &AuthentCode[8] );
  
  RetCode = SglAuthentB(
		  LibRandNum);

  if( RetCode != SGL_SUCCESS ) {
      return SGL_AUTHENTICATION_FAILED;
  }  
  
  return SGL_SUCCESS;

}


// Signing functions
unsigned  int
SglSignData( 
	unsigned int ProductId,
	unsigned int *AppSignKey,
	unsigned int LockSignKeyNum,
	unsigned int Mode,
	unsigned int LockSignInterval,
	unsigned int DataLen,
	unsigned int *Data,
	unsigned int *Signature ) {

	return SglSignDataComb(
					ProductId,
					AppSignKey,
					LockSignKeyNum,
					Mode,
					LockSignInterval,
					DataLen,
					Data,
					Signature );

}

#define SGL_SIGN_DATA_INITVECTOR_1   0xC4F8424E
#define SGL_SIGN_DATA_INITVECTOR_2   0xAB99A60C
#define SGL_SIGN_DATA_FILLUPDATA     0xF6A67A11

unsigned  int
SglSignDataApp( 
	unsigned int *SignKey,
	unsigned int Mode,
	unsigned int DataLen,
	unsigned int *Data,
	unsigned int *Signature ) {


	unsigned int FeedBackRegister[2];
	unsigned int DataIndexMax;
	unsigned int i;
	unsigned  int   RetCode;

	if( DataLen == 0 ) {
		return SGL_PARAMETER_INVALID;
	}
	
	FeedBackRegister[0]= SGL_SIGN_DATA_INITVECTOR_1;
	FeedBackRegister[1]= SGL_SIGN_DATA_INITVECTOR_2;
	
	DataIndexMax= DataLen - 1;
	
	for( i=0; i<DataIndexMax; i=i+2 ) {
		FeedBackRegister[0]= Data[i]   ^ FeedBackRegister[0];
		FeedBackRegister[1]= Data[i+1] ^ FeedBackRegister[1];
		SglTeaEncipher( FeedBackRegister, FeedBackRegister, SignKey );
	}

	if( (DataLen % 2)==1 ) {
		FeedBackRegister[0]= Data[i]    ^ FeedBackRegister[0];
		FeedBackRegister[1]= SGL_SIGN_DATA_FILLUPDATA ^ FeedBackRegister[1];
		SglTeaEncipher( FeedBackRegister, FeedBackRegister, SignKey );
	}

	switch( Mode ) {
		
		case SGL_SIGNATURE_GENERATE:
			Signature[0]= FeedBackRegister[0];
			Signature[1]= FeedBackRegister[1];
			RetCode= SGL_SUCCESS;
			break;

		case SGL_SIGNATURE_VERIFY:
			if(( Signature[0] == FeedBackRegister[0] ) &&
			   ( Signature[1] == FeedBackRegister[1] )) {
				RetCode= SGL_SUCCESS;
			} else {
				RetCode= SGL_SIGNATURE_INVALID;
			}

			break;

		default:
				RetCode= SGL_PARAMETER_INVALID;

	}

	return RetCode;

}


unsigned  int
SglSignDataLock( 
	unsigned  int ProductId,
	unsigned  int SignKeyNum,
	unsigned  int Mode,
	unsigned  int DataLen,
	unsigned  int *Data,
	unsigned  int *Signature ) {


	unsigned  int   FeedBackRegister[2];
	unsigned  int 	DataIndexMax;
	unsigned  int   i;
	unsigned  int   RetCode;

	
	if( DataLen == 0 ) {
		return SGL_PARAMETER_INVALID;
	}

	
	FeedBackRegister[0]= SGL_SIGN_DATA_INITVECTOR_1;
	FeedBackRegister[1]= SGL_SIGN_DATA_INITVECTOR_2;
	
	DataIndexMax= DataLen - 1;
	
	for( i=0; i<DataIndexMax; i=i+2 ) {
		FeedBackRegister[0]= Data[i]   ^ FeedBackRegister[0];
		FeedBackRegister[1]= Data[i+1] ^ FeedBackRegister[1];

		RetCode= SglCryptLock(
					ProductId,
					SignKeyNum,
					0,
					1,
					FeedBackRegister);

		if( RetCode != SGL_SUCCESS ) {
			return RetCode;
		}
		
	}

	if( (DataLen % 2)==1 ) {
		FeedBackRegister[0]= Data[i]    ^ FeedBackRegister[0];
		FeedBackRegister[1]= SGL_SIGN_DATA_FILLUPDATA ^ FeedBackRegister[1];

		RetCode= SglCryptLock(
					ProductId,
					SignKeyNum,
					0,
					1,
					FeedBackRegister);

		if( RetCode != SGL_SUCCESS ) {
			return RetCode;
		}

	}

	switch( Mode ) {
		
		case SGL_SIGNATURE_GENERATE:
			Signature[0]= FeedBackRegister[0];
			Signature[1]= FeedBackRegister[1];
			RetCode= SGL_SUCCESS;
			break;

		case SGL_SIGNATURE_VERIFY:
			if(( Signature[0] == FeedBackRegister[0] ) &&
			   ( Signature[1] == FeedBackRegister[1] )) {
				RetCode= SGL_SUCCESS;
			} else {
				RetCode= SGL_SIGNATURE_INVALID;
			}
			break;

		default:
				RetCode= SGL_PARAMETER_INVALID;

	}

	return RetCode;

}


unsigned  int
SglSignDataComb( 
	unsigned  int ProductId,
	unsigned  int *AppSignKey,
	unsigned  int LockSignKeyNum,
	unsigned  int Mode,
	unsigned  int LockSignInterval,
	unsigned  int DataLen,
	unsigned  int *Data,
	unsigned  int *Signature ) {


	unsigned  int   FeedBackRegister[2];
	unsigned  int 	DataIndexMax;
	unsigned  int   i;
	unsigned  int   Interval;
	unsigned  int   RetCode;

	
	if( DataLen == 0 ) {
		return SGL_PARAMETER_INVALID;
	}
	
	if( LockSignInterval == 0 ) {
		return SGL_PARAMETER_INVALID;
	}
	
	DataIndexMax= DataLen - 1;
	Interval= 0x01L << LockSignInterval;
	

	FeedBackRegister[0]= SGL_SIGN_DATA_INITVECTOR_1;
	FeedBackRegister[1]= SGL_SIGN_DATA_INITVECTOR_2;
	
	
	for( i=0; i<DataIndexMax; i=i+2 ) {
		FeedBackRegister[0]= Data[i]   ^ FeedBackRegister[0];
		FeedBackRegister[1]= Data[i+1] ^ FeedBackRegister[1];

		if( (i % Interval) == 0 ) {
			
			RetCode= SglCryptLock(
						ProductId,
						LockSignKeyNum,
						0,
						1,
						FeedBackRegister);

			if( RetCode != SGL_SUCCESS ) {
				return RetCode;
			}
			
		} else {
			SglTeaEncipher( FeedBackRegister, FeedBackRegister, AppSignKey );
		}
		
	}

	if( (DataLen % 2)==1 ) {
		FeedBackRegister[0]= Data[i]    ^ FeedBackRegister[0];
		FeedBackRegister[1]= SGL_SIGN_DATA_FILLUPDATA ^ FeedBackRegister[1];

		if( (i % Interval) == 0 ) {

			RetCode= SglCryptLock(
						ProductId,
						LockSignKeyNum,
						0,
						1,
						FeedBackRegister);

			if( RetCode != SGL_SUCCESS ) {
				return RetCode;
			}

		} else {
			SglTeaEncipher( FeedBackRegister, FeedBackRegister, AppSignKey );
		}

	}

	switch( Mode ) {
		
		case SGL_SIGNATURE_GENERATE:
			Signature[0]= FeedBackRegister[0];
			Signature[1]= FeedBackRegister[1];
			RetCode= SGL_SUCCESS;
			break;

		case SGL_SIGNATURE_VERIFY:
			if(( Signature[0] == FeedBackRegister[0] ) &&
			   ( Signature[1] == FeedBackRegister[1] )) {
				RetCode= SGL_SUCCESS;
			} else {
				RetCode= SGL_SIGNATURE_INVALID;
			}
			break;

		default:
				RetCode= SGL_PARAMETER_INVALID;

	}

	return RetCode;

}


/****************************************************************************/

void SglTeaEncipher(
    const unsigned int *const   InData,
    unsigned int  *const         OutData,
    const unsigned int * const  Key) {
    
    register unsigned int y=InData[0];
    register unsigned int z=InData[1];
    register unsigned int sum=0;
    register unsigned int delta=0x9E3779B9;
    register unsigned int a=Key[0];
    register unsigned int b=Key[1];
    register unsigned int c=Key[2];
    register unsigned int d=Key[3];
    register unsigned int n=32;

    
    while( n-->0 ) {
        sum += delta;
        y += (z << 4)+a ^ z+sum ^ (z >> 5)+b;
        z += (y << 4)+c ^ y+sum ^ (y >> 5)+d;
    }

    OutData[0]=y;
    OutData[1]=z;
    
}



void SglTeaDecipher(
    const unsigned  int *const   InData,
    unsigned  int *const         OutData,
    const unsigned  int * const  Key) {
    
    register unsigned int y=InData[0];
    register unsigned int z=InData[1];
    register unsigned int sum=0xC6EF3720;
    register unsigned int delta=0x9E3779B9;
    register unsigned int a=Key[0];
    register unsigned int b=Key[1];
    register unsigned int c=Key[2];
    register unsigned int d=Key[3];
    register unsigned int n=32;

    /* sum = delta<<5, in general sum = delta * n */

    while( n-->0 ) {
        z -= (y << 4)+c ^ y+sum ^ (y >> 5)+d;
        y -= (z << 4)+a ^ z+sum ^ (z >> 5)+b;
        sum -= delta;
    }
   
    OutData[0]=y;
    OutData[1]=z;
    
}
#ifdef __cplusplus
}
#endif

