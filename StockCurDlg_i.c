/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu May 21 14:34:38 2009
 */
/* Compiler settings for D:\°í°´\StockCurDlg\StockCurDlg.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID LIBID_StockCurDlgLib = {0x9BADB75B,0xDB1E,0x4E52,{0x9F,0x81,0x65,0x3F,0xE3,0x19,0x28,0xA5}};


#ifdef __cplusplus
}
#endif

