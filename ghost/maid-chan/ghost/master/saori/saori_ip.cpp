#pragma warning(disable: 4503)
#pragma warning(disable: 4786)

#include <vector>
#include <map>
#include <string>
#include <winsock2.h>
#include <windows.h>
using namespace std;

//文字列を切り分ける
void SplitString(char *szString, const char *szDelimiter, vector<char*> &vDest) {
  int nDelimLength = strlen(szDelimiter);
  while (true) {
    vDest.push_back(szString);
    szString = strstr(szString, szDelimiter);
    if (!szString)
      break;
    *szString = '\0';
    szString += nDelimLength;
  }
}

//数値を文字列に変換
string ToStr(int val) {
  char buf[32];
  _itoa(val, buf, 10);
  return buf;
}

extern "C" __declspec(dllexport) HGLOBAL __cdecl request(HGLOBAL h, long *len) { 
  //パース
  char *szTmp = new char[*len + 1];
  memcpy(szTmp, (char*)h, *len);
  szTmp[*len] = '\0';
  GlobalFree(h);

  vector<char*> vpLine;
  SplitString(szTmp, "\r\n", vpLine);
  vector<char*> vpColumn;
  char *p = strstr(vpLine[0], " SAORI/");
  string strCommand(vpLine[0], p - vpLine[0]);
  string strProtoVer = p + 1;

  map<string, string> mReq;
  for (UINT i = 1; i < vpLine.size(); ++i) {
    char *p = strchr(vpLine[i], ':');
    if (!p)
      break;
    *p = '\0';
    mReq.insert(map<string, string>::value_type(vpLine[i], p + 2));
  }
  map<string, string> mRes;

  bool bFromLocal = mReq.count("SecurityLevel") == 0 || stricmp(mReq["SecurityLevel"].c_str(), "local") == 0;
  int status = 200;

  //実作業
	WORD wVersionRequested; 
	WSADATA wsaData; 
	char name[255]; 
	char* ip; 
	PHOSTENT hostinfo; 
	wVersionRequested = MAKEWORD( 2, 0 ); 
	if ( WSAStartup( wVersionRequested, &wsaData ) == 0 ) 
	{ 
		if( gethostname ( name, sizeof(name)) == 0) 
		{ 
			if((hostinfo = gethostbyname(name)) != NULL) 
			{ 
				ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list); 
			} 
		} 
		WSACleanup( );
	} 

 //実作業
  if (strCommand == "GET Version") {
  } else if (strCommand == "EXECUTE") {
    string &strCmd = mReq["Argument0"];
    if (strCmd == "host") {
      mRes["Result"] = name;
    }else if (strCmd == "ip") {
      mRes["Result"] = ip;
	}
  } else {
    status = 400;
  }

  //応答生成
  string strRes;
  if (status == 200) {
    strRes = strProtoVer + " 200 OK\r\n";
    for (map<string, string>::iterator i = mRes.begin(); i != mRes.end(); ++i)
      strRes += i->first + ": " + i->second + "\r\n";
    strRes += "\r\n";

  } else if (status == 204) {
    strRes = strProtoVer + " 204 No Content\r\n\r\n";

  } else if (status == 400) {
    strRes = "SAORI/1.0 400 Bad Request\r\n\r\n";

  } else {
    strRes = strProtoVer + " " + ToStr(status) + " OK\r\n\r\n";
  }
  *len = strRes.length();
  char *pRes = (char*)GlobalAlloc(GMEM_FIXED, *len + 1);
  memcpy(pRes, strRes.c_str(), *len + 1);
  return (HGLOBAL)pRes;
}

extern "C" __declspec(dllexport) BOOL __cdecl load(HGLOBAL h, long len) {
  GlobalFree(h);
  return TRUE;
}

extern "C" __declspec(dllexport) BOOL __cdecl unload(void) {
  return TRUE;
}

bool APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
    DisableThreadLibraryCalls((HINSTANCE)hModule);
  } else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
    unload();
  }
  return true;
}
