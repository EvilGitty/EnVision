
#include <stdio.h>
#include ".\..\SglW32.h"


void main() {

    unsigned int   ReturnCode;
    unsigned int   ProductId;
    unsigned int   SerialNumber;
    unsigned int   Adr;
    unsigned int   Cnt;
    unsigned int   ConfigData[8];
    unsigned int   Data[256];
    unsigned int   DateSigned[5];
    unsigned int   i;

  
    unsigned int   AuthentCode[12] = {   // This authentiction code is only for DEMO
                            0xF574D17B,  // modules. Every company gets its own  
                            0xA94628EE,  // authentication code, when starting to purchase   
                            0xF2857A8F,  // full release modules.
                            0x69346B4A,  // This is a security feature that prevents 'dummy' 
                            0x4136E8F2,  // DLLs or applications to act as the original ones
                            0x89ADC688,
                            0x80C2C1D4,
                            0xA8C6327C,
                            0x1A72699A,
                            0x574B7CA0,
                            0x1E8D3E98,
                            0xD7DEFDC5 };



    ProductId = 0x0001;        // 16-bit value, that can be used to give different porducts
                               // of a company different IDs, which makes it easier to 
                               // distinguish between theese products. 
                               // DEMOs have product ID 0x0001


    printf("\nSG-Lock test program by SG Intec Ltd & Co. KG (C) 2008\n" );
    printf("Searching SG-Lock with ProductId %d ...\n", ProductId ); 

    // first we authenticate us (the application) to the library and vice versa)
    // this has to be done once BEFORE using other functions of the API in the case
    // that the library is loaded statically. In the case you load the library dynamically
    // ( Windows LoadLibrary function) you have to do it every time after loading
    ReturnCode = SglAuthent( AuthentCode );
    if( ReturnCode != SGL_SUCCESS ) {
        printf( "SglAuthent: Error returned! (code: 0x%X)\n", ReturnCode );
        return;
    }

    // lets see whether we find a SG-Lock DEMO module ....
    ReturnCode = SglSearchLock( ProductId );
    if( ReturnCode != SGL_SUCCESS ) {
        if( ReturnCode == SGL_DGL_NOT_FOUND ) {
            printf( "No SG-Lock found!\n" );
            printf( "Please Plug SG-Lock in and test again!\n" );

        } else {
            printf( "SglSearchLock: Error returned! (code: 0x%X)\n", ReturnCode );
        }
        return;
    }

    printf( "SG-Lock found!\n" );


    // ... found. Ok. Lets read the serial number.
    ReturnCode = SglReadSerialNumber( ProductId, &SerialNumber );
    if( ReturnCode != SGL_SUCCESS ) {
        printf( "SglReadSerialNumber: Error returned! (code: 0x%X)\n", ReturnCode );
        return;
    } else {
        printf( "SG-Lock serial number: %d\n", SerialNumber );
    }


    // read SG-Lock informations }

    ReturnCode = SglReadConfig( ProductId, SGL_READ_CONFIG_LOCK_INFO, ConfigData );

    if( ReturnCode  == SGL_SUCCESS ) {
        if( ConfigData[1] == SGL_CONFIG_INTERFACE_USB ) {
            printf( "SG-Lock type: U%d\n", ConfigData[0]+1 );
        } else {
            printf( "SG-Lock type: L%d\n", ConfigData[0]+1 );
        }
    } else {
        printf( "SglReadConfig: error: %d\n", ReturnCode) ;
    }


    // check if we have memory and counters U3/U4/L3/L4 and NOT U2/L2 }
    if( ConfigData[0] != 1 ) {

        // Lets read some data ...
        Adr= 0;  // read from start of memory  
	    Cnt= 4;  // 4 DWORDs
	
	    // theese functions are not supported by the 2 series - only 3 and 4 series
        ReturnCode = SglReadData( ProductId, Adr, Cnt, Data );
        if( ReturnCode != SGL_SUCCESS ) {
            printf( "SglReadData: Error returned! (code: 0x%X)\n", ReturnCode );
            return;
        } else {
            printf( "SG-Lock data read:\n" );
       	    for( i=0; i<Cnt; i++) {
	           	printf("Adr %d: 0x%8.8X\n", Adr+i, Data[i]);
	        }
        }

        printf( "SG-Lock counter read:\n" );
        for( i=0; i<4; i++) {
	
            ReturnCode = SglReadCounter( ProductId, i, Data );
		    if( ReturnCode != SGL_SUCCESS ) {
	            printf( "SglReadCounter: Error returned! (code: 0x%X)\n", ReturnCode );
                return;
            } else {
                printf("Cnt %d: 0x%8.8X\n", i, Data[0]);
            }
        }
    }


    // Let's sign some data. We use a common date with day/month/year and store also
    // the 64-bit signature n the data field.

    DateSigned[0]= 31;
    DateSigned[1]= 12;
    DateSigned[2]= 2005;


    printf( "SG-Lock signing functions:\n" );
  
    ReturnCode= SglSignDataLock(
                    ProductId,
                    0,
                    SGL_SIGNATURE_GENERATE,
                    (sizeof(DateSigned)/4) - 2,
                    DateSigned,
                    &DateSigned[3]);

    if( ReturnCode != SGL_SUCCESS ) {
        if( ReturnCode == SGL_DGL_NOT_FOUND ) {
            printf( "SG-Lock not found!\n" );
        } else {
            printf( "SglSearchLock: Error returned! (code: 0x%X)\n", ReturnCode );
            return;
        }
    } 


    printf( "Signing date %d %d %d, signature is: 0x%8.8X 0x%8.8X\n",
            DateSigned[0], DateSigned[1], DateSigned[2], DateSigned[3], DateSigned[4]);

    // Uncomment the next line to simulate data manipulation
    //DateSigned[0]= 30;

    printf( "Verifing signature ... ");

    ReturnCode= SglSignDataLock(
                    ProductId,
                    0,
                    SGL_SIGNATURE_VERIFY,
                    (sizeof(DateSigned)/4) - 2,
                    DateSigned,
                    &DateSigned[3]);


  	switch( ReturnCode ) {
    	case SGL_SUCCESS:
           	printf( "Date valid!\n" );
           	break;
        case SGL_SIGNATURE_INVALID:
           	printf( "Date INVALID!\n" );
            break;
      	case SGL_DGL_NOT_FOUND:
           	printf( "SG-Lock not found!\n" );
           	return;
      	default:
           	printf( "SglSearchLock: Error returned! (code: 0x%X)\n", ReturnCode );

  	}



}
