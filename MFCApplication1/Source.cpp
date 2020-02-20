#include "stdafx.h"
#include "Source.h"

void delay(int Time)
{long t1,t2;
 t1=GetTickCount();
 do{
 t2=GetTickCount();
 }while(t2-t1<Time);
 }

unsigned char HexToInt(char* s)
{
char hexch[] = "0123456789ABCDEF";
int i,j,t;
unsigned char n,k;
unsigned char r;
//int r;
char ch;
/*CString ss2;
t=strlen(s);
ss2.Format(_T("%d"),t);
AfxMessageBox(ss2);*/
k=1; 
r=0;
for (i=strlen(s);  i>0; i--) {
   	ch = s[i-1]; if (ch > 0x3f) ch &= 0xDF;
   	n = 0;
    for (j = 0; j<16; j++)
      	if (ch == hexch[j])
         	n = j;
    	r += (n*k);
     	k *= 16;
	}
  	return r;
}

int Char16ToInt(char c)  
{  
    int num;  
    num = 0;//  
    switch (c)  
    {  
    case '0':  
            num = 0;  
            break;  
    case '1':  
            num = 1;  
            break;  
    case '2':  
            num = 2;  
            break;  
    case '3':  
            num = 3;  
            break;  
    case '4':  
            num = 4;  
            break;  
    case '5':  
            num = 5;  
            break;  
    case '6':  
            num = 6;  
            break;  
    case '7':  
            num = 7;  
            break;  
    case '8':  
            num = 8;  
            break;  
    case '9':  
            num = 9;  
            break;  
    case 'a':  
    case 'A':  
            num = 10;  
            break;  
    case 'b':  
    case 'B':  
            num = 11;  
            break;  
    case 'c':  
    case 'C':  
            num = 12;  
            break;  
    case 'd':  
    case 'D':  
            num = 13;  
            break;  
    case 'e':  
    case 'E':  
            num = 14;  
            break;  
    case 'f':  
    case 'F':  
            num = 15;  
            break;  
    default:  
        break;  
    }  
    return num;  
}
int StrToNumber16(const char *str)  
{  
    int len,i,num;  
    CString ss2;
	num = 0;//使用数据必须初始化否则产生不确定值  
    len = strlen(str);  
    for (i = 0; i < len; i++)  
    {  
  //   AfxMessageBox(CString(str[i]));
		//num = num*16 + Char16ToInt(str[i]);/*十六进制字符串与10进制的对应数据*/   
        num=num+pow(16.0,len-1-i)*Char16ToInt(str[i]);
	//ss2.Format(_T("%d"),num);
//AfxMessageBox(ss2);
	}  
  


	return num;  
  
}


string HexToBin(const string &strHex)
 {
     if (strHex.size() % 2 != 0)
     {
         return "";
     }
 
     string strBin;
     strBin.resize(strHex.size() / 2);
     for (size_t i = 0; i < strBin.size(); i++)
     {
         uint8_t cTemp = 0;
         for (size_t j = 0; j < 2; j++)
         {
             char cCur = strHex[2 * i + j];
             if (cCur >= '0' && cCur <= '9')
             {
                 cTemp = (cTemp << 4) + (cCur - '0');
            }
             else if (cCur >= 'a' && cCur <= 'f')
             {
                cTemp = (cTemp << 4) + (cCur - 'a' + 10);
             }
             else if (cCur >= 'A' && cCur <= 'F')
             {
                 cTemp = (cTemp << 4) + (cCur - 'A' + 10);
             }
             else
             {
                 return "";
            }
         }
         strBin[i] = cTemp;
     }
 
     return strBin;
 }

WORD DEC( CString str )
 {
  WORD decvalue=0;
  int i=0;
  //char buffshi[256];
 for( i=0 ; i<str.GetLength() ; i++)
  {
   if(str[i]>= 'a'&&str[i]<='f')
   {
    decvalue*=16;
    decvalue+=str[i]-'f'+15;
   }
   else if ((str[i]>='A') && (str[i]<='F'))     
   {
    decvalue*=16;
    decvalue+=str[i]-'F'+15;
   }
   else if(str[i]>='0'&&str[i]<='9')
   {
    decvalue*=16;
    decvalue+=str[i] - '0';
   }
 // sprintf_s(buffshi, "%d",decvalue);
//AfxMessageBox(CString(buffshi));
 }
  return decvalue;
 }

CString DECToBIN( int idata )
 {
  CString tempStr, outStr;

 int iBIN[32];//存储每bit二进制的数组
 int i = 0;
  while (idata)
  {
   iBIN[i] = idata%2;

  idata = idata/2;
   i++;
  }
  for (int j = i-1; j >= 0; j--)
  {
   tempStr.Format(L"%d", iBIN[j]);
   outStr = outStr + tempStr;
  }
  return outStr;
 }


