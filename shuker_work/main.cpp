#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <windows.h>  //Sleep
#include <time.h>
#include <algorithm>

#include "mysql_escape.h"

using namespace std;

void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c) {
  v.clear();
  std::string::size_type pos1, pos2;
  pos2 = s.find(c);
  pos1 = 0;
  while(std::string::npos != pos2) {
    v.push_back(s.substr(pos1, pos2-pos1));
 
    pos1 = pos2 + c.size();
    pos2 = s.find(c, pos1);
  }
  if(pos1 != s.length())
    v.push_back(s.substr(pos1));
}

void testMysqlEscape() {
  cout << "---###---func testMysqlEscape() start---" << endl;
  
  string a = "\'xx\"";
  string b = EscapeString2(a);
  printf("a:%s\n", a.c_str());
  printf("b:%s\n", b.c_str());
  
  cout << "---###---func testMysqlEscape() end---" << endl;
  system("PAUSE");
  return;
}

void myFileOp() {
  /*
   * ifstream -- 从已有的文件读
   * ofstream -- 向文件写内容
   * fstream  -- 打开文件供读写
   * fstream有两个子类:ifstream(input file stream),ofstream(outpu file stream);ifstream默认以输入方式打开文件,而ofstream默认以输出方式打开文件
   */
  cout << "---###---func myFileOp() start---" << endl;
  
  /*
  ofstream ofile("myFileOpW.txt",ios::app);
  ofile << "haha" << ":[" << 5 << "]" << endl;
  ofile.close();
  */
  
  /*
  ifstream ifile("myFileOpR.txt",ios::in);
  if(!ifile) {  //重载了!运算符
      cout << "---error: open R_file fail" << "---" << endl;
      return;
  }
  string strLineR;
  int iLineNumR = 1;
  while(getline(ifile, strLineR)) {  //读utf8中文文件会有乱码
     cout << "---LineR[" << iLineNumR << "]:(" << strLineR << ")---" << endl;
      iLineNumR++;
  }
  ifile.close();
  */
  
  fstream iofile("myFileOpRW.txt");  //0-定位在开头 //等同:iofile.open("c:\\config.sys"); 等同:iofile.open("c:\\config.sys",ios::in|ios::out,0);
  if(!iofile) {  //重载了!运算符
      cout << "---error: open RW_file fail" << "---" << endl;
      return;
  }
  ofstream ofile2;
  ofile2.open("myFileOpRW_2.txt");  //等同:ios::out|ios::trunc
  if(!ofile2) {  //重载了!运算符
      cout << "---error: open W_file2 fail" << "---" << endl;
      return;
  }
  iofile.close();
  ofile2.close();
  
  cout << "---###---func myFileOp() end---" << endl;
  system("PAUSE");
  return;
}

void myAssFileOp(string p_strOpFileName = "", string p_strRetFileName = "", int p_iOpSec = 0) {
  cout << "---###---func myAssFileOp() start---" << endl;
  
  string strOpFileName, strRetFileName;
  int iOpSec = 0;
  
  if(p_strOpFileName == "") {
      cout << "---input strOpFileName---" << endl;
      cin >> strOpFileName;
  }
  else {
      strOpFileName = p_strOpFileName;
  }
  if(p_strRetFileName == "") {
      cout << "---input strRetFileName---" << endl;
      cin >> strRetFileName;
  }
  else {
      strRetFileName = p_strRetFileName;
  }
  if(p_iOpSec == 0) {
      cout << "---input iOpSec[>0:delay <0:ahead]---" << endl;
      cin >> iOpSec;  //>0:delay <0:ahead
  }
  else {
      iOpSec = p_iOpSec;
  }
  if(iOpSec == 0) {
      cout << "---error: param:opSec=0---" << endl;
      return;
  }
  
  strOpFileName += ".ass";
  strRetFileName += ".ass";
  
  fstream iofile(strOpFileName.c_str());  //0-定位在开头 //等同:iofile.open("c:\\config.sys"); 等同:iofile.open("c:\\config.sys",ios::in|ios::out,0);
  if(!iofile) {  //重载了!运算符
      cout << "---error: open " << strOpFileName << " fail" << "---" << endl;
      return;
  }
  ofstream ofile;
  ofile.open(strRetFileName.c_str());  //等同:ios::out|ios::trunc
  if(!ofile) {  //重载了!运算符
      cout << "---error: open " << strRetFileName << " fail" << "---" << endl;
      return;
  }
  
  //Dialogue: 0,0:00:58.40,0:00:59.57,*Default,NTP,0,0,0,,我去看看\N{\fn微软雅黑}{\b0}{\fs14}{\3c&H202020&}{\shad1}I'm gonna go check it out.
  string strLine;
  int iLineNum = 1;
  string strFlag = "Dialogue";
  while(getline(iofile, strLine)) {
      if(strLine.find(strFlag) != string::npos) {
		  int i_b_hour_pos = 12;
		  int i_b_min_pos = 14;
		  int i_b_sec_pos = 17;
		  int i_e_hour_pos = 23;
		  int i_e_min_pos = 25;
		  int i_e_sec_pos = 28;
		  string str_b_hour = strLine.substr(i_b_hour_pos,1);  //hour只有一位 h:mm:ss.xx 所以最长只能9小时
		  string str_b_min = strLine.substr(i_b_min_pos,2);
		  string str_b_sec = strLine.substr(i_b_sec_pos,2);
		  string str_e_hour = strLine.substr(i_e_hour_pos,1);
		  string str_e_min = strLine.substr(i_e_min_pos,2);
		  string str_e_sec = strLine.substr(i_e_sec_pos,2);
		  //cout << "---oldLine[" << iLineNum << "]:(" << strLine << ")---" << endl;
		  //cout << "---oldLine[" << iLineNum << "]:(" << str_b_hour << ":" << str_b_min << ":" << str_b_sec << "," << str_e_hour << ":" << str_e_min << ":" << str_e_sec << ")---" << endl;
		  
		  int iAddMin = 0;
		  int iAddHour = 0;
		  int i_sec_pos, i_min_pos, i_hour_pos;
		  string str_sec, str_min, str_hour;
		  char tmp[8] = {};
		  for(int i=0; i<2; i++) {
		      if(i == 0) {
			      i_sec_pos = i_b_sec_pos;
				  i_min_pos = i_b_min_pos;
				  i_hour_pos = i_b_hour_pos;
				  str_sec = str_b_sec;
				  str_min = str_b_min;
				  str_hour = str_b_hour;
			  }
			  else {
			      i_sec_pos = i_e_sec_pos;
				  i_min_pos = i_e_min_pos;
				  i_hour_pos = i_e_hour_pos;
				  str_sec = str_e_sec;
				  str_min = str_e_min;
				  str_hour = str_e_hour;
			  }
			  
			  if(iOpSec > 0) {  //delay iOpSec seconds
			      int i_sec = atoi(str_sec.c_str());
		          i_sec += iOpSec;
		          iAddMin = i_sec/60;
		          i_sec %= 60;
		          if(i_sec < 10) {
		              snprintf(tmp,sizeof(tmp),"0%d",i_sec);
		          }
		          else {
		              snprintf(tmp,sizeof(tmp),"%d",i_sec);
		          }
		          strLine.replace(i_sec_pos, 2, tmp, 2);
		          if(iAddMin > 0) {
		              int i_min = atoi(str_min.c_str());
		              i_min += iAddMin;
		              iAddHour = i_min/60;
		              i_min %= 60;
		              if(i_min < 10) {
		                  snprintf(tmp,sizeof(tmp),"0%d",i_min);
		              }
		              else {
		                  snprintf(tmp,sizeof(tmp),"%d",i_min);
		              }
		              strLine.replace(i_min_pos, 2, tmp, 2);
		              if(iAddHour > 0) {
		                  int i_hour = atoi(str_hour.c_str());
		                  i_hour += iAddHour;
						  if(i_hour < 10) {  //[0,9]
		                      snprintf(tmp,sizeof(tmp),"%d",i_hour);
		                      strLine.replace(i_hour_pos, 1, tmp, 1);
						  }
						  else {  //hour只有一位 h:mm:ss.xx 所以最长只能9小时
						      char err[64] = {0};
							  snprintf(err,sizeof(err),"---error: oldLine[%d]:(hour can not delay %ds, over 10h)---",iLineNum,iOpSec);
							  strLine = err;
							  cout << strLine << endl;
							  break;
						  }
		              }
		          }
			  }
			  else {  //ahead iOpSec seconds
			      int i_sec = atoi(str_sec.c_str());
				  i_sec += iOpSec;
				  if(i_sec >= 10) {
				      snprintf(tmp,sizeof(tmp),"%d",i_sec);
					  strLine.replace(i_sec_pos, 2, tmp, 2);
				  }
				  else if(i_sec >= 0) {
				      snprintf(tmp,sizeof(tmp),"0%d",i_sec);
					  strLine.replace(i_sec_pos, 2, tmp, 2);
				  }
				  else {
				      iAddMin = -1 + i_sec/60;
					  i_sec += (-1)*iAddMin*60;
					  if(i_sec < 10) {
		                  snprintf(tmp,sizeof(tmp),"0%d",i_sec);
		              }
		              else {
		                  snprintf(tmp,sizeof(tmp),"%d",i_sec);
		              }
		              strLine.replace(i_sec_pos, 2, tmp, 2);
					  int i_min = atoi(str_min.c_str());
					  i_min += iAddMin;
					  if(i_min >= 10) {
					      snprintf(tmp,sizeof(tmp),"%d",i_min);
					      strLine.replace(i_min_pos, 2, tmp, 2);
					  }
					  else if(i_min >= 0) {
					      snprintf(tmp,sizeof(tmp),"0%d",i_min);
					      strLine.replace(i_min_pos, 2, tmp, 2);
					  }
					  else {
					      iAddHour = -1 + i_min/60;
						  i_min += (-1)*iAddHour*60;
						  if(i_min < 10) {
		                      snprintf(tmp,sizeof(tmp),"0%d",i_min);
		                  }
		                  else {
		                      snprintf(tmp,sizeof(tmp),"%d",i_min);
		                  }
		                  strLine.replace(i_min_pos, 2, tmp, 2);
						  int i_hour = atoi(str_hour.c_str());
		                  i_hour += iAddHour;
						  if(i_hour >= 0) {
						      snprintf(tmp,sizeof(tmp),"%d",i_hour);
		                      strLine.replace(i_hour_pos, 1, tmp, 1);
						  }
						  else {  //时间不够ahead
							  char err[64] = {0};
							  snprintf(err,sizeof(err),"---error: oldLine[%d]:(can not ahead %ds)---",iLineNum,iOpSec);
							  strLine = err;
							  cout << strLine << endl;
							  break;
						  }
					  }
				  }
			  }
		  }
		  //cout << "---newLine[" << iLineNum << "]:(" << strLine << ")---" << endl;
	  }
	  ofile << strLine << endl;
	  iLineNum++;
  }
  iofile.close();
  ofile.close();
  
  cout << "---###---func myAssFileOp() end---" << endl;
  system("PAUSE");
  return;
}

void mySrtFileOp(string p_strOpFileName = "", string p_strRetFileName = "", int p_iOpSec = 0) {
  cout << "---###---func mySrtFileOp() start---" << endl;
  
  string strOpFileName, strRetFileName;
  int iOpSec = 0;
  
  if(p_strOpFileName == "") {
      cout << "---input strOpFileName---" << endl;
      cin >> strOpFileName;
  }
  else {
      strOpFileName = p_strOpFileName;
  }
  if(p_strRetFileName == "") {
      cout << "---input strRetFileName---" << endl;
      cin >> strRetFileName;
  }
  else {
      strRetFileName = p_strRetFileName;
  }
  if(p_iOpSec == 0) {
      cout << "---input iOpSec[>0:delay <0:ahead]---" << endl;
      cin >> iOpSec;  //>0:delay <0:ahead
  }
  else {
      iOpSec = p_iOpSec;
  }
  if(iOpSec == 0) {
      cout << "---error: param:opSec=0---" << endl;
      return;
  }
  
  strOpFileName += ".srt";
  strRetFileName += ".srt";
  
  fstream iofile(strOpFileName.c_str());  //0-定位在开头 //等同:iofile.open("c:\\config.sys"); 等同:iofile.open("c:\\config.sys",ios::in|ios::out,0);
  if(!iofile) {  //重载了!运算符
      cout << "---error: open " << strOpFileName << " fail" << "---" << endl;
      return;
  }
  ofstream ofile;
  ofile.open(strRetFileName.c_str());  //等同:ios::out|ios::trunc
  if(!ofile) {  //重载了!运算符
      cout << "---error: open " << strRetFileName << " fail" << "---" << endl;
      return;
  }
  
  //00:00:22,500 --> 00:00:24,100
  string strLine;
  int iLineNum = 1;
  string strFlag = "-->";
  while(getline(iofile, strLine)) {
      if(strLine.find(strFlag) != string::npos) {
		  int i_b_hour_pos = 0;
		  int i_b_min_pos = 3;
		  int i_b_sec_pos = 6;
		  int i_e_hour_pos = 17;
		  int i_e_min_pos = 20;
		  int i_e_sec_pos = 23;
		  string str_b_hour = strLine.substr(i_b_hour_pos,2);
		  string str_b_min = strLine.substr(i_b_min_pos,2);
		  string str_b_sec = strLine.substr(i_b_sec_pos,2);
		  string str_e_hour = strLine.substr(i_e_hour_pos,2);
		  string str_e_min = strLine.substr(i_e_min_pos,2);
		  string str_e_sec = strLine.substr(i_e_sec_pos,2);
		  //cout << "---oldLine[" << iLineNum << "]:(" << strLine << ")---" << endl;
		  //cout << "---oldLine[" << iLineNum << "]:(" << str_b_hour << ":" << str_b_min << ":" << str_b_sec << "," << str_e_hour << ":" << str_e_min << ":" << str_e_sec << ")---" << endl;
		  
		  int iAddMin = 0;
		  int iAddHour = 0;
		  int i_sec_pos, i_min_pos, i_hour_pos;
		  string str_sec, str_min, str_hour;
		  char tmp[8] = {};
		  for(int i=0; i<2; i++) {
		      if(i == 0) {
			      i_sec_pos = i_b_sec_pos;
				  i_min_pos = i_b_min_pos;
				  i_hour_pos = i_b_hour_pos;
				  str_sec = str_b_sec;
				  str_min = str_b_min;
				  str_hour = str_b_hour;
			  }
			  else {
			      i_sec_pos = i_e_sec_pos;
				  i_min_pos = i_e_min_pos;
				  i_hour_pos = i_e_hour_pos;
				  str_sec = str_e_sec;
				  str_min = str_e_min;
				  str_hour = str_e_hour;
			  }
			  
			  if(iOpSec > 0) {  //delay iOpSec seconds
			      int i_sec = atoi(str_sec.c_str());
		          i_sec += iOpSec;
		          iAddMin = i_sec/60;
		          i_sec %= 60;
		          if(i_sec < 10) {
		              snprintf(tmp,sizeof(tmp),"0%d",i_sec);
		          }
		          else {
		              snprintf(tmp,sizeof(tmp),"%d",i_sec);
		          }
		          strLine.replace(i_sec_pos, 2, tmp, 2);
		          if(iAddMin > 0) {
		              int i_min = atoi(str_min.c_str());
		              i_min += iAddMin;
		              iAddHour = i_min/60;
		              i_min %= 60;
		              if(i_min < 10) {
		                  snprintf(tmp,sizeof(tmp),"0%d",i_min);
		              }
		              else {
		                  snprintf(tmp,sizeof(tmp),"%d",i_min);
		              }
		              strLine.replace(i_min_pos, 2, tmp, 2);
		              if(iAddHour > 0) {
		                  int i_hour = atoi(str_hour.c_str());
		                  i_hour += iAddHour;
						   if(i_hour < 10) {
		                       snprintf(tmp,sizeof(tmp),"0%d",i_hour);
		                   }
		                   else {
		                       snprintf(tmp,sizeof(tmp),"%d",i_hour);
		                   }
		                  strLine.replace(i_hour_pos, 2, tmp, 2);
		              }
		          }
			  }
			  else {  //ahead iOpSec seconds
			      int i_sec = atoi(str_sec.c_str());
				  i_sec += iOpSec;
				  if(i_sec >= 10) {
				      snprintf(tmp,sizeof(tmp),"%d",i_sec);
					  strLine.replace(i_sec_pos, 2, tmp, 2);
				  }
				  else if(i_sec >= 0) {
				      snprintf(tmp,sizeof(tmp),"0%d",i_sec);
					  strLine.replace(i_sec_pos, 2, tmp, 2);
				  }
				  else {
				      iAddMin = -1 + i_sec/60;
					  i_sec += (-1)*iAddMin*60;
					  if(i_sec < 10) {
		                  snprintf(tmp,sizeof(tmp),"0%d",i_sec);
		              }
		              else {
		                  snprintf(tmp,sizeof(tmp),"%d",i_sec);
		              }
		              strLine.replace(i_sec_pos, 2, tmp, 2);
					  int i_min = atoi(str_min.c_str());
					  i_min += iAddMin;
					  if(i_min >= 10) {
					      snprintf(tmp,sizeof(tmp),"%d",i_min);
					      strLine.replace(i_min_pos, 2, tmp, 2);
					  }
					  else if(i_min >= 0) {
					      snprintf(tmp,sizeof(tmp),"0%d",i_min);
					      strLine.replace(i_min_pos, 2, tmp, 2);
					  }
					  else {
					      iAddHour = -1 + i_min/60;
						  i_min += (-1)*iAddHour*60;
						  if(i_min < 10) {
		                      snprintf(tmp,sizeof(tmp),"0%d",i_min);
		                  }
		                  else {
		                      snprintf(tmp,sizeof(tmp),"%d",i_min);
		                  }
		                  strLine.replace(i_min_pos, 2, tmp, 2);
						  int i_hour = atoi(str_hour.c_str());
		                  i_hour += iAddHour;
						  if(i_hour >= 10) {
						      snprintf(tmp,sizeof(tmp),"%d",i_hour);
		                      strLine.replace(i_hour_pos, 2, tmp, 2);
						  }
						  else if(i_hour >= 0) {
						      snprintf(tmp,sizeof(tmp),"0%d",i_hour);
		                      strLine.replace(i_hour_pos, 2, tmp, 2);
						  }
						  else {  //时间不够ahead
							  char err[64] = {0};
							  snprintf(err,sizeof(err),"---error: oldLine[%d]:(can not ahead %ds)---",iLineNum,iOpSec);
							  strLine = err;
							  cout << strLine << endl;
							  break;
						  }
					  }
				  }
			  }
		  }
		  //cout << "---newLine[" << iLineNum << "]:(" << strLine << ")---" << endl;
	  }
	  ofile << strLine << endl;
	  iLineNum++;
  }
  iofile.close();
  ofile.close();
  
  cout << "---###---func mySrtFileOp() end---" << endl;
  system("PAUSE");
  return;
}

void myTime() {
     cout << "---###---func myTime() start---" << endl;
	 
	 time_t tTime = time(NULL);
     char szTime[16] = {0};
     strftime(szTime,sizeof(szTime),"%X",localtime(&tTime));
     printf("tTime:%u\nszTime:%s\n",tTime,szTime);
     
     cout << "---###---func myTime() end---" << endl;
     system("PAUSE");
     return;
}

void puzzleA() {
     cout << "---###---func puzzleA() start---" << endl;
	 
	 map<int, vector<string> > mapSum;
     map<int, map<string, int> > mapProduct;  //因为乙先问 则乙的数据结构和甲不同 
     char szNumber[128] = {0};
     for(int i=1; i<=30; i++) {
         for(int j=i+1; j<=30; j++) {
             int iSum = i + j;
             int iProduct = i * j;
             snprintf(szNumber, sizeof(szNumber), "%d_%d", i, j);
             mapSum[iSum].push_back(szNumber);
             mapProduct[iProduct][szNumber] = iSum;
         }
     }
     for(map<int, vector<string> >::iterator it=mapSum.begin(); it!=mapSum.end(); it++) {
         cout << "----sum:" << it->first << endl;
         for(unsigned int ui=0; ui<it->second.size(); ui++) {
             cout << "--:" << it->second[ui] << endl;
         }
     }
     for(map<int, map<string, int> >::iterator it=mapProduct.begin(); it!=mapProduct.end(); it++) {
         cout << "----product:" << it->first << endl;
         for(map<string, int>::iterator it_2=it->second.begin(); it_2!=it->second.end(); it_2++) {
             cout << "--:" << it_2->first << " - " << it_2->second << endl;
         }
     }
     //乙先问 必须从乙开始
     vector<int> vecSumRet;
     vector<int> vecProductRet;
     for(map<int, map<string, int> >::iterator it=mapProduct.begin(); it!=mapProduct.end(); it++) {
         if(it->second.size() > 1) {
             int flag = 0;
             string strRet;
             for(map<string, int>::iterator it_2=it->second.begin(); it_2!=it->second.end(); it_2++) {
                 map<int, vector<string> >::iterator it_3 = mapSum.find(it_2->second);
                 if(it_3!=mapSum.end() && it_3->second.size()>1) {
                     flag++;
                     strRet = it_2->second;
                 }
                 if(flag > 1) {
                     break;
                 }
             }
             if(flag == 1) {
                 cout << "----ret----" << strRet << endl;
             }
         }
     }
     /*for(unsigned int ui=0; ui<vecSumRet.size(); ui++) {
         cout << "----sum:" << vecSumRet[ui] << endl;
         for(unsigned int ui_2=0; ui_2<mapSum[vecSumRet[ui]].size(); ui_2++) {
             cout << "--:" << mapSum[vecSumRet[ui]][ui_2] << endl;
         }
     }
     for(unsigned int ui=0; ui<vecProductRet.size(); ui++) {
         cout << "----product:" << vecProductRet[ui] << endl;
         for(map<string, int>::iterator it=mapProduct[vecProductRet[ui]].begin(); it!=mapProduct[vecProductRet[ui]].end(); it++) {
             cout << "--:" << it->first << " - " << it->second << endl;
         }
     }*/
     
     cout << "---###---func puzzleA() end---" << endl;
     system("PAUSE");
     return;
}

/*
 * 排列组合
 * Arrangement & Combination
 * A(n,m) = n!/(n-m)!
 * C(n,m) = A(n,m)/m! = n!/(n-m)!/m!;
 */
//提供给'C_n_m'调用 不单独调用
void C_n_m_private(vector< vector<unsigned int> > &vecRes, vector<unsigned int> &vecTmpRes, unsigned int n, unsigned int m, int unsigned uiBegin, bool bCout) {
	 if(vecTmpRes.size() < m) {
         cout << "---error: [C_n_m_private]a invalid param vecTmpRes.size:" << vecTmpRes.size() << "<m:" << m << "---" << endl;
         return;
     }
	
	 if(n<m || m==0) {
         cout << "---error: [C_n_m_private]a invalid param n:" << n << ";m:" << m << "---" << endl;
         return;
     }
	 //n>=m && n!=0 && m!=0
	 else if(m == n) {
		for(unsigned int ui=0;ui<m;ui++) {
			vecTmpRes[vecTmpRes.size()-m+ui] = uiBegin+ui;
		}
		vecRes.push_back(vecTmpRes);
		if(bCout) {
			for(unsigned int uiSz=0;uiSz<vecTmpRes.size();uiSz++) {
				cout << vecTmpRes[uiSz] << ";";
			}
			cout << endl;
		}
	 }
	 //n>m
	 else if(m == 1) {
		for(unsigned int ui=0;ui<n;ui++) {
			vecTmpRes[vecTmpRes.size()-1] = uiBegin+ui;
			vecRes.push_back(vecTmpRes);
			if(bCout) {
				for(unsigned int uiSz=0;uiSz<vecTmpRes.size();uiSz++) {
					cout << vecTmpRes[uiSz] << ";";
				}
				cout << endl;
			}
		}
	 }
	 else {
		 for(unsigned int ui=uiBegin;ui<=uiBegin+n-m;ui++) {
			vecTmpRes[vecTmpRes.size()-m] = ui;
			C_n_m_private(vecRes, vecTmpRes, n-ui+uiBegin-1, m-1, ui+1, bCout);
		 }
	 }
}
//n>=m,无序从n中选出m,iS表示起始数;如 n=5,m=3,uiBegin=2表示从2,3,4,5,6中选3个数
unsigned int C_n_m(vector< vector<unsigned int> > &vecRes, unsigned int n, unsigned int m, bool bCout=false, int unsigned uiBegin=0) {
	vecRes.clear();       //vecRes must be cleared, then call func-C_n_m_private
	vector<unsigned int> vecTmpRes;
	vecTmpRes.resize(m);  //vecTmpRes's size must = m, then call func-C_n_m_private
	C_n_m_private(vecRes, vecTmpRes, n, m, uiBegin, bCout);
	return vecRes.size();
}

void CnA() {
	int ret = 0;
	vector< vector<unsigned int> > vecRet;
	unsigned int n = 7;
	unsigned int m = 5;
	bool bCout = true;
	ret = C_n_m(vecRet,n,m,bCout);
	cout << "C(" << n << "," << m << ")=" << ret << endl;
}

/*
 *Texas Hold'em Poker
 *皇家同花顺-Royal straight flush；同花顺-Straight flush；四条（金刚）-Four of a kind；葫芦-Full house(Boat)；
 *同花-Flush；顺子-Straight；三条-Three of a kind；两对-Two pairs；一对-One pair；高牌 -High hand
 *Suit:s=spade;h=heart;c=club;d=diamond;j=JOKER(red j;black j)
 */
class myCard {
public:
      myCard() {
          iFigure = 0;
          strSuit = "z";
          bFlag = false;
      }
	  
	  //a-点数 b-花色 14-留给A 15-black j 16-red j
	  myCard(int a, string b) {
          if((a>=1 && a<=13 && (b=="s"||b=="h"||b=="c"||b=="d")) || (a>=15 && a<=16 && b=="j")) {
              iFigure = a;
              strSuit = b;
              bFlag = true;
          }
          else {
              iFigure = 0;
              strSuit = "z";
              bFlag = false;
              cout << "---error: this is a invalid card---" << endl;
          }
      }
      
	  void assignCard(myCard oCard) {
	      iFigure = oCard.iFigure;
		  strSuit = oCard.strSuit;
		  bFlag = oCard.bFlag;
	  }
	  
      string prtCard() {
           char szRes[4] = {0};
           
           if(!bFlag) {
               cout << "---error: this is a invalid card---" << endl;
               snprintf(szRes,sizeof(szRes),"0z");
               return szRes;
           }
           
           if(iFigure>1 && iFigure<10) {
               snprintf(szRes,sizeof(szRes),"%d%s",iFigure,strSuit.c_str());
           }
           else if(iFigure==1) {
               snprintf(szRes,sizeof(szRes),"A%s",strSuit.c_str());
           }
           else if(iFigure==10) {
               snprintf(szRes,sizeof(szRes),"T%s",strSuit.c_str());
           }
           else if(iFigure==11) {
               snprintf(szRes,sizeof(szRes),"J%s",strSuit.c_str());
           }
           else if(iFigure==12) {
               snprintf(szRes,sizeof(szRes),"Q%s",strSuit.c_str());
           }
           else if(iFigure==13) {
               snprintf(szRes,sizeof(szRes),"K%s",strSuit.c_str());
           }
           else if(iFigure==15) {
               snprintf(szRes,sizeof(szRes),"B%s",strSuit.c_str());
           }
           else if(iFigure==16) {
               snprintf(szRes,sizeof(szRes),"R%s",strSuit.c_str());
           }
           return szRes;
      }
      
      int getFigure() {
          if(!bFlag) {
              cout << "---error: this is a invalid card---" << endl;
          }
          
          return iFigure;
      }
      
      string getSuit() {
          if(!bFlag) {
              cout << "---error: this is a invalid card---" << endl;
          }
          
          return strSuit;
      } 
      
private:
      int iFigure;
      string strSuit;
      bool bFlag;
};

class myPoker {
public:
      myPoker(int iNum, int iPack=1) {
          map<int,string> mapSuit;
          mapSuit[1] = "s"; mapSuit[2] = "h"; mapSuit[3] = "c"; mapSuit[4] = "d"; mapSuit[5] = "j";
          if(iNum == 52) {
              for(int p=1;p<=iPack;p++) {
                  for(int i=1;i<=4;i++) {
                      for(int j=1;j<=13;j++) {
                          myCard oCard(j,mapSuit[i]);
                          vecCards.push_back(oCard);
                      }
                  }
              }
          }
          else if(iNum == 54) {
              for(int p=1;p<=iPack;p++) {
                  for(int i=1;i<=4;i++) {
                      for(int j=1;j<=13;j++) {
                          myCard oCard(j,mapSuit[i]);
                          vecCards.push_back(oCard);
                      }
                  }
                  for(int j=15;j<=16;j++) {
                      myCard oCard(j,mapSuit[5]);
                      vecCards.push_back(oCard);
                  }
              }
          }
          else {
              cout << "---error: invalid card num---" << endl;
          }
      }
      
      unsigned int shuffle(unsigned int uiSeed) {
		  srand(uiSeed);  //不能直接用time(NULL) 否则在for循环里洗牌同1秒内种子都相同，多次执行同样的序列洗牌后牌会被回归原样
          int iIdx;
          int iSize = (int)vecCards.size();
          for(int i=0;i<iSize;i++) {
              iIdx = i + rand()%(iSize-i);
              swap(vecCards[iIdx], vecCards[i]);
          }
		  unsigned int uiNextSeed = rand();
          return uiNextSeed;
      }
      
	  //uiIdx 从1起
      void prtCardByIdx(unsigned int uiIdx, bool bIdx=false) {
           if(uiIdx>vecCards.size() || uiIdx==0) {
                cout << "---prtCardByIdx error: this is a invalid card idx---" << endl;
                return;
           }
           if(bIdx) {
               cout << ":[" << uiIdx << "]" << vecCards[uiIdx-1].prtCard() << endl;
           }
           else {
               cout << vecCards[uiIdx-1].prtCard() << endl;
           }
           return;
      }
      
      unsigned int getCardNum() {
          return vecCards.size();
      }
      
	  //uiIdx 从1起
	  void getCardByIdx(unsigned int uiIdx, myCard &oCard) {
          if(uiIdx>vecCards.size() || uiIdx==0) {
              cout << "---getCardByIdx error: this is a invalid card idx---" << endl;
              return;
          }
		  oCard.assignCard(vecCards[uiIdx-1]);
		  return;
	  }
	  
      void get5Cards(vector<myCard> &vec) {
           vec.assign(vecCards.begin(), vecCards.begin()+5);
           return;
      }

private:
      vector<myCard> vecCards;
};

//打印一手牌
void prtCards(vector<myCard> &vecCards) {
	for(unsigned int ui=0;ui<vecCards.size();ui++) {
		cout << vecCards[ui].prtCard() << endl;
	}
}

/**
 *|RoyalStraightFlush|Y| | | | | | | | |
 *|StraightFlush     |M|Y| | | | | | | |
 *|FourOfAKind       | | |Y| | | | | | |
 *|FullHouse         | | | |Y| | | | | |
 *|Flush             |M|M| | |Y| | | | |
 *|Straight          |M|M| | | |Y| | | |
 *|ThreeOfAKind      | | | | | | |Y| | |
 *|TwoPairs          | | | | | | | |Y| |
 *|OnePair           | | | | | | | | |Y|
**/

bool isFlush(vector<myCard> &vecCards) {
     if(vecCards.size() != 5) {
         cout << "---error: [isFlush]a invalid cards num:" << vecCards.size() << "---" << endl;
         return false;
     }
     
     if((vecCards[0].getSuit()==vecCards[1].getSuit())&&
        (vecCards[0].getSuit()==vecCards[2].getSuit())&&
        (vecCards[0].getSuit()==vecCards[3].getSuit())&&
        (vecCards[0].getSuit()==vecCards[4].getSuit())) {
         return true;
     }
     else {
         return false;
     }
}

bool isStraight(vector<myCard> &vecCards, int &iTJQKA) {
     if(vecCards.size() != 5) {
         cout << "---error: [isStraight]a invalid cards num:" << vecCards.size() << "---" << endl;
         return false;
     }
	 
	 iTJQKA = 0;
     
     vector<int> vecFigure;
     for(unsigned int ui=0;ui<vecCards.size();ui++) {
         vecFigure.push_back(vecCards[ui].getFigure());
     }
     sort(vecFigure.begin(), vecFigure.end());
     if((vecFigure[0]+1==vecFigure[1])&&
        (vecFigure[0]+2==vecFigure[2])&&
        (vecFigure[0]+3==vecFigure[3])&&
        (vecFigure[0]+4==vecFigure[4])) {
         return true;
     }
     else if(vecFigure[0]==1 && vecFigure[1]==10 && vecFigure[2]==11 && vecFigure[3]==12 && vecFigure[4]==13) {  //TJQKA
		iTJQKA = 1;
        return true;
     }
     else {
         return false;
     }
}

bool isStraightFlush(vector<myCard> &vecCards, int &iTJQKA) {
     if(vecCards.size() != 5) {
         cout << "---error: [isStraightFlush]a invalid cards num:" << vecCards.size() << "---" << endl;
         return false;
     }
     
	 iTJQKA = 0;
	 
     if(isFlush(vecCards) && isStraight(vecCards, iTJQKA)) {
         return true;
     }
     else {
         return false;
     }
}

bool isRoyalStraightFlush(vector<myCard> &vecCards) {
     if(vecCards.size() != 5) {
         cout << "---error: [isRoyalStraightFlush]a invalid cards num:" << vecCards.size() << "---" << endl;
         return false;
     }
     
	 int iTJQKA = 0;
     if(isStraightFlush(vecCards, iTJQKA) && iTJQKA) {
         return true;
     }
     else {
         return false;
     }
}

bool isFourOfAKind(vector<myCard> &vecCards) {
	if(vecCards.size() != 5) {
		cout << "---error: [isFourOfAKind]a invalid cards num:" << vecCards.size() << "---" << endl;
		return false;
	}
	
	map<int,int> mapFigureCnt;
	map<int,int>::iterator it;
	for(unsigned int ui=0;ui<vecCards.size();ui++) {
		it = mapFigureCnt.find(vecCards[ui].getFigure());
		if(it == mapFigureCnt.end()) {
			mapFigureCnt[vecCards[ui].getFigure()] = 1;
		}
		else {
			mapFigureCnt[vecCards[ui].getFigure()] += 1;
		}
    }
	
	it = mapFigureCnt.begin();
	if(mapFigureCnt.size()==2 && (it->second==1 || it->second==4)) {
		return true;
	}
	else {
		return false;
	}
}

bool isFullHouse(vector<myCard> &vecCards) {
	if(vecCards.size() != 5) {
		cout << "---error: [isFullHouse]a invalid cards num:" << vecCards.size() << "---" << endl;
		return false;
	}
	
	map<int,int> mapFigureCnt;
	map<int,int>::iterator it;
	for(unsigned int ui=0;ui<vecCards.size();ui++) {
		it = mapFigureCnt.find(vecCards[ui].getFigure());
		if(it == mapFigureCnt.end()) {
			mapFigureCnt[vecCards[ui].getFigure()] = 1;
		}
		else {
			mapFigureCnt[vecCards[ui].getFigure()] += 1;
		}
    }
	
	it = mapFigureCnt.begin();
	if(mapFigureCnt.size()==2 && (it->second==2 || it->second==3)) {
		return true;
	}
	else {
		return false;
	}
}

bool isThreeOfAKind(vector<myCard> &vecCards) {
	if(vecCards.size() != 5) {
		cout << "---error: [isThreeOfAKind]a invalid cards num:" << vecCards.size() << "---" << endl;
		return false;
	}
	
	map<int,int> mapFigureCnt;
	map<int,int>::iterator it;
	for(unsigned int ui=0;ui<vecCards.size();ui++) {
		it = mapFigureCnt.find(vecCards[ui].getFigure());
		if(it == mapFigureCnt.end()) {
			mapFigureCnt[vecCards[ui].getFigure()] = 1;
		}
		else {
			mapFigureCnt[vecCards[ui].getFigure()] += 1;
		}
    }
	
	it = mapFigureCnt.begin();
	if(mapFigureCnt.size() == 3) {
		if(it->second == 3) {
			return true;
		}
		else if((++it)->second == 3) {  //++it->x等同++(it->x); (it++)->x取到it->x的值; it++->x等同(it++)->x
			return true;
		}
		else if((++it)->second == 3) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool isTwoPairs(vector<myCard> &vecCards) {
	if(vecCards.size() != 5) {
		cout << "---error: [isTwoPairs]a invalid cards num:" << vecCards.size() << "---" << endl;
		return false;
	}
	
	map<int,int> mapFigureCnt;
	map<int,int>::iterator it;
	for(unsigned int ui=0;ui<vecCards.size();ui++) {
		it = mapFigureCnt.find(vecCards[ui].getFigure());
		if(it == mapFigureCnt.end()) {
			mapFigureCnt[vecCards[ui].getFigure()] = 1;
		}
		else {
			mapFigureCnt[vecCards[ui].getFigure()] += 1;
		}
    }
	
	it = mapFigureCnt.begin();
	if(mapFigureCnt.size() == 3) {
		if(it->second == 2) {
			return true;
		}
		else if((++it)->second == 2) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool isOnePair(vector<myCard> &vecCards) {
	if(vecCards.size() != 5) {
		cout << "---error: [isOnePair]a invalid cards num:" << vecCards.size() << "---" << endl;
		return false;
	}
	
	map<int,int> mapFigureCnt;
	map<int,int>::iterator it;
	for(unsigned int ui=0;ui<vecCards.size();ui++) {
		it = mapFigureCnt.find(vecCards[ui].getFigure());
		if(it == mapFigureCnt.end()) {
			mapFigureCnt[vecCards[ui].getFigure()] = 1;
		}
		else {
			mapFigureCnt[vecCards[ui].getFigure()] += 1;
		}
    }
	
	if(mapFigureCnt.size() == 4) {
		return true;
	}
	else {
		return false;
	}
}

/*牌型
 *RoyalStraightFlush=10;
 *StraightFlush      =9;
 *FourOfAKind        =8;
 *FullHouse          =7;
 *Flush              =6;
 *Straight           =5;
 *ThreeOfAKind       =4;
 *TwoPairs           =3;
 *OnePair            =2;
 *HighHand           =1;
 *error              =0;
 */
#define ROYALSTRAIGHTFLUSH 10
#define STRAIGHTFLUSH       9
#define FOUROFAKIND         8
#define FULLHOUSE           7
#define FLUSH               6
#define STRAIGHT            5
#define THREEOFAKIND        4
#define TWOPAIRS            3
#define ONEPAIR             2
#define HIGHHAND            1
class texasHands {
public:
	texasHands() {
		mapHands[ROYALSTRAIGHTFLUSH] = "RoyalStraightFlush";
		mapHands[STRAIGHTFLUSH] = "StraightFlush";
		mapHands[FOUROFAKIND] = "FourOfAKind";
		mapHands[FULLHOUSE] = "FullHouse";
		mapHands[FLUSH] = "Flush";
		mapHands[STRAIGHT] = "Straight";
		mapHands[THREEOFAKIND] = "ThreeOfAKind";
		mapHands[TWOPAIRS] = "TwoPairs";
		mapHands[ONEPAIR] = "OnePair";
		mapHands[HIGHHAND] = "HighHand";
		mapHands[0] = "error";
	}
	
	string getTexasHands(int iCode) {
		string res;
		map<int, string>::iterator it = mapHands.find(iCode);
		if(it != mapHands.end()) {
			res = it->second;
		}
		else {
			res = "notFound";
		}
		return res;
	}

private:
	map<int, string> mapHands;
};
static texasHands oTexasHands;

/*5张牌计算牌型 采用'mapHands'的定义返回牌型code
 *并按可比较的点数降序排列 如3333K 22Q87
 *A=14 K=13 Q=12 J=11
 */
int getHand(vector<myCard> &vecCards, vector<int> &vecSortedFigures) {
	if(vecCards.size() != 5) {
		cout << "---error: [getHand]a invalid cards num:" << vecCards.size() << "---" << endl;
		return 0;
	}
	
	vecSortedFigures.clear();
	
	int iHand = 0;
	int iTJQKA = 0;
	if(isRoyalStraightFlush(vecCards)) {
		iHand = ROYALSTRAIGHTFLUSH;
		//cout << "---RoyalStraightFlush---" << endl;
		vecSortedFigures.push_back(14);
		vecSortedFigures.push_back(13);
		vecSortedFigures.push_back(12);
		vecSortedFigures.push_back(11);
		vecSortedFigures.push_back(10);
	}
	else if(isStraightFlush(vecCards, iTJQKA)) {  //iTJQKA must equal 0
		iHand = STRAIGHTFLUSH;
		//cout << "---StraightFlush---" << endl;
		vecSortedFigures.push_back(vecCards[0].getFigure());
		vecSortedFigures.push_back(vecCards[1].getFigure());
		vecSortedFigures.push_back(vecCards[2].getFigure());
		vecSortedFigures.push_back(vecCards[3].getFigure());
		vecSortedFigures.push_back(vecCards[4].getFigure());
		sort(vecSortedFigures.begin(), vecSortedFigures.end(), greater<int>());
	}
	else if(isFourOfAKind(vecCards)) {
		iHand = FOUROFAKIND;
		//cout << "---FourOfAKind---" << endl;
		map<int,int> mapFigureCnt;
		map<int,int>::iterator it;
		for(unsigned int ui=0;ui<vecCards.size();ui++) {
			it = mapFigureCnt.find(vecCards[ui].getFigure()==1?14:vecCards[ui].getFigure());
			if(it == mapFigureCnt.end()) {
				mapFigureCnt[vecCards[ui].getFigure()==1?14:vecCards[ui].getFigure()] = 1;
			}
			else {
				mapFigureCnt[vecCards[ui].getFigure()==1?14:vecCards[ui].getFigure()] += 1;
			}
		}
		//mapFigureCnt一定是[4|1 OR 1|4]
		it=mapFigureCnt.begin();
		if(it->second == 4) {
			vecSortedFigures.push_back(it->first);
			vecSortedFigures.push_back(it->first);
			vecSortedFigures.push_back(it->first);
			vecSortedFigures.push_back(it->first);
			vecSortedFigures.push_back((++it)->first);
		}
		else {
			vecSortedFigures.push_back((++it)->first);
			vecSortedFigures.push_back(it->first);
			vecSortedFigures.push_back(it->first);
			vecSortedFigures.push_back(it->first);
			vecSortedFigures.push_back((--it)->first);
		}
	}
	else if(isFullHouse(vecCards)) {
		iHand = FULLHOUSE;
		//cout << "---FullHouse---" << endl;
		map<int,int> mapFigureCnt;
		map<int,int>::iterator it;
		for(unsigned int ui=0;ui<vecCards.size();ui++) {
			it = mapFigureCnt.find(vecCards[ui].getFigure()==1?14:vecCards[ui].getFigure());
			if(it == mapFigureCnt.end()) {
				mapFigureCnt[vecCards[ui].getFigure()==1?14:vecCards[ui].getFigure()] = 1;
			}
			else {
				mapFigureCnt[vecCards[ui].getFigure()==1?14:vecCards[ui].getFigure()] += 1;
			}
		}
		//mapFigureCnt一定是[3|2 OR 2|3]
		it=mapFigureCnt.begin();
		if(it->second == 3) {
			vecSortedFigures.push_back(it->first);
			vecSortedFigures.push_back(it->first);
			vecSortedFigures.push_back(it->first);
			vecSortedFigures.push_back((++it)->first);
			vecSortedFigures.push_back(it->first);
		}
		else {
			vecSortedFigures.push_back((++it)->first);
			vecSortedFigures.push_back(it->first);
			vecSortedFigures.push_back(it->first);
			vecSortedFigures.push_back((--it)->first);
			vecSortedFigures.push_back(it->first);
		}
	}
	else if(isFlush(vecCards)) {
		iHand = FLUSH;
		//cout << "---Flush---" << endl;
		vecSortedFigures.push_back(vecCards[0].getFigure()==1?14:vecCards[0].getFigure());
		vecSortedFigures.push_back(vecCards[1].getFigure()==1?14:vecCards[1].getFigure());
		vecSortedFigures.push_back(vecCards[2].getFigure()==1?14:vecCards[2].getFigure());
		vecSortedFigures.push_back(vecCards[3].getFigure()==1?14:vecCards[3].getFigure());
		vecSortedFigures.push_back(vecCards[4].getFigure()==1?14:vecCards[4].getFigure());
		sort(vecSortedFigures.begin(), vecSortedFigures.end(), greater<int>());
	}
	else if(isStraight(vecCards, iTJQKA)) {
		iHand = STRAIGHT;
		//cout << "---Straight---" << endl;
		if(iTJQKA) {
			vecSortedFigures.push_back(14);
			vecSortedFigures.push_back(13);
			vecSortedFigures.push_back(12);
			vecSortedFigures.push_back(11);
			vecSortedFigures.push_back(10);
		}
		else {
			vecSortedFigures.push_back(vecCards[0].getFigure());
			vecSortedFigures.push_back(vecCards[1].getFigure());
			vecSortedFigures.push_back(vecCards[2].getFigure());
			vecSortedFigures.push_back(vecCards[3].getFigure());
			vecSortedFigures.push_back(vecCards[4].getFigure());
			sort(vecSortedFigures.begin(), vecSortedFigures.end(), greater<int>());
		}
	}
	else if(isThreeOfAKind(vecCards)) {
		iHand = THREEOFAKIND;
		//cout << "---ThreeOfAKind---" << endl;
		map<int,int> mapFigureCnt;
		map<int,int>::iterator it;
		for(unsigned int ui=0;ui<vecCards.size();ui++) {
			it = mapFigureCnt.find(vecCards[ui].getFigure()==1?14:vecCards[ui].getFigure());
			if(it == mapFigureCnt.end()) {
				mapFigureCnt[vecCards[ui].getFigure()==1?14:vecCards[ui].getFigure()] = 1;
			}
			else {
				mapFigureCnt[vecCards[ui].getFigure()==1?14:vecCards[ui].getFigure()] += 1;
			}
		}
		//map的特性: 会以key的值自行排序 从小到大
		//mapFigureCnt一定是[3|1|1 OR 1|3|1 OR 1|1|3]
		int fig_1_s = 0;
		int fig_1_b = 0;  //fig_1_b>fig_1_s
		for(it=mapFigureCnt.begin();it!=mapFigureCnt.end();it++) {
			if(it->second == 3) {
				vecSortedFigures.push_back(it->first);
				vecSortedFigures.push_back(it->first);
				vecSortedFigures.push_back(it->first);
			}
			else {
				if(fig_1_s == 0) {
					fig_1_s = it->first;
				}
				else {
					fig_1_b = it->first;
				}
			}
		}
		vecSortedFigures.push_back(fig_1_b);
		vecSortedFigures.push_back(fig_1_s);
	}
	else if(isTwoPairs(vecCards)) {
		iHand = TWOPAIRS;
		//cout << "---TwoPairs---" << endl;
		map<int,int> mapFigureCnt;
		map<int,int>::iterator it;
		for(unsigned int ui=0;ui<vecCards.size();ui++) {
			it = mapFigureCnt.find(vecCards[ui].getFigure()==1?14:vecCards[ui].getFigure());
			if(it == mapFigureCnt.end()) {
				mapFigureCnt[vecCards[ui].getFigure()==1?14:vecCards[ui].getFigure()] = 1;
			}
			else {
				mapFigureCnt[vecCards[ui].getFigure()==1?14:vecCards[ui].getFigure()] += 1;
			}
		}
		//map的特性: 会以key的值自行排序 从小到大
		//mapFigureCnt一定是[2|2|1 OR 2|1|2 OR 2|2|1]
		int fig_1 = 0;
		int fig_2 = 0;
		for(it=mapFigureCnt.begin();it!=mapFigureCnt.end();it++) {
			if(it->second == 2) {
				if(fig_2 == 0) {
					fig_2 = it->first;
				}
				else {
					vecSortedFigures.push_back(it->first);
					vecSortedFigures.push_back(it->first);
				}
			}
			else {
				fig_1 = it->first;
			}
		}
		vecSortedFigures.push_back(fig_2);
		vecSortedFigures.push_back(fig_2);
		vecSortedFigures.push_back(fig_1);
	}
	else if(isOnePair(vecCards)) {
		iHand = ONEPAIR;
		//cout << "---OnePair---" << endl;
		map<int,int> mapFigureCnt;
		map<int,int>::iterator it;
		for(unsigned int ui=0;ui<vecCards.size();ui++) {
			it = mapFigureCnt.find(vecCards[ui].getFigure()==1?14:vecCards[ui].getFigure());
			if(it == mapFigureCnt.end()) {
				mapFigureCnt[vecCards[ui].getFigure()==1?14:vecCards[ui].getFigure()] = 1;
			}
			else {
				mapFigureCnt[vecCards[ui].getFigure()==1?14:vecCards[ui].getFigure()] += 1;
			}
		}
		//map的特性: 会以key的值自行排序 从小到大
		//mapFigureCnt一定是[2|1|1|1 OR 1|2|1|1 OR 1|1|2|1 OR 1|1|1|2]
		int fig_1_s = 0;
		int fig_1_m = 0;
		int fig_1_b = 0;  //fig_1_b > fig_1_m > fig_1_s
		for(it=mapFigureCnt.begin();it!=mapFigureCnt.end();it++) {
			if(it->second == 2) {
				vecSortedFigures.push_back(it->first);
				vecSortedFigures.push_back(it->first);
			}
			else {
				if(fig_1_s == 0) {
					fig_1_s = it->first;
				}
				else if(fig_1_m == 0) {
					fig_1_m = it->first;
				}
				else {
					fig_1_b = it->first;
				}
			}
		}
		vecSortedFigures.push_back(fig_1_b);
		vecSortedFigures.push_back(fig_1_m);
		vecSortedFigures.push_back(fig_1_s);
	}
	else {
		iHand = HIGHHAND;
		//cout << "---HighHand---" << endl;
		vecSortedFigures.push_back(vecCards[0].getFigure()==1?14:vecCards[0].getFigure());
		vecSortedFigures.push_back(vecCards[1].getFigure()==1?14:vecCards[1].getFigure());
		vecSortedFigures.push_back(vecCards[2].getFigure()==1?14:vecCards[2].getFigure());
		vecSortedFigures.push_back(vecCards[3].getFigure()==1?14:vecCards[3].getFigure());
		vecSortedFigures.push_back(vecCards[4].getFigure()==1?14:vecCards[4].getFigure());
		sort(vecSortedFigures.begin(), vecSortedFigures.end(), greater<int>());
	}
	
	return iHand;
}

//比较2个牌型大小 -1:error 0:A=B 1:A<B 2:A>B
int compare2Hands(vector<myCard> &vecCards_A, vector<myCard> &vecCards_B, int &iWinHand) {
	if(vecCards_A.size()!=5 || vecCards_B.size()!=5) {
		cout << "---error: [compare2Hands]a invalid cards num:" << vecCards_A.size() << "|" << vecCards_B.size() << "---" << endl;
		return -1;
	}
	
	int iHand_A = 0;
	int iHand_B = 0;
	vector<int> vecSortedFigures_A;
	vector<int> vecSortedFigures_B;
	iHand_A = getHand(vecCards_A, vecSortedFigures_A);
	iHand_B = getHand(vecCards_B, vecSortedFigures_B);
	if(iHand_A==0 || iHand_B==0 || vecSortedFigures_A.size()!=5 || vecSortedFigures_B.size()!=5) {
		cout << "---error: [compare2Hands]a invalid getHand ret:" << iHand_A << "|" << iHand_B << "; vecF_sz:" << vecSortedFigures_A.size() << vecSortedFigures_B.size() << "---" << endl;
		return -1;
	}
	
	iWinHand = iHand_A;
	if(iHand_A > iHand_B) {
		return 2;
	}
	else if(iHand_A < iHand_B) {
		iWinHand = iHand_B;
		return 1;
	}
	else {
		for(int i=0;i<5;i++) {
			if(vecSortedFigures_A[i] > vecSortedFigures_B[i]) {
				return 2;
			}
			else if(vecSortedFigures_A[i] < vecSortedFigures_B[i]) {
				iWinHand = iHand_B;
				return 1;
			}
			else {
				continue;
			}
		}
		return 0;
	}
}
//比较X个牌型大小
void compareXHands(vector< vector<myCard> > &vecCardsArr, unsigned int &uiWinIdx, int &iWinHand) {
	if(vecCardsArr.empty()) {
		cout << "---error: [compareXHands]a invalid cardsArr : empty---" << endl;
		return;
	}
	
	uiWinIdx = 0;
	iWinHand = 0;
	vector<myCard> vecWinCards;
	vecWinCards.assign(vecCardsArr[0].begin(), vecCardsArr[0].end());
	for(unsigned int ui=0;ui!=vecCardsArr.size();ui++) {
		if(vecCardsArr[ui].size() != 5) {
			cout << "---error: [compareXHands]a invalid cardsArr[" << ui << "] num:" << vecCardsArr[ui].size() << "---" << endl;
			return;
		}
		
		int ret = compare2Hands(vecWinCards, vecCardsArr[ui], iWinHand);
		if(ret == 1) {
			uiWinIdx = ui;
			vecWinCards.assign(vecCardsArr[ui].begin(), vecCardsArr[ui].end());
		}
		else if(ret==0 || ret==2) {
			continue;
		}
		else {
			cout << "---error: [compareXHands] call compare2Hands error:" << ret << "---" << endl;
			return;
		}
	}
}

/*X张牌计算牌型 采用'mapHands'的定义返回牌型code
 *'vecWinCards'为最高牌型
 */
int getHandInX(vector<myCard> &vecCards, vector<myCard> &vecWinCards) {
	unsigned int uiSz = vecCards.size();
	if(uiSz < 5) {
		cout << "---error: [getHandInX]a invalid cards num:" << uiSz << "---" << endl;
		return 0;
	}
	
	if(uiSz != 7) {
		cout << "---warn: [getHandInX]an unnormal cards num:" << uiSz << "---" << endl;
	}
	
	vector< vector<unsigned int> > vecRes;
	unsigned int n = uiSz;
	unsigned int m = 5;
	C_n_m(vecRes,n,m);
	
	vector< vector<myCard> > vecCardsArr;
	for(unsigned int ui=0;ui!=vecRes.size();ui++) {
		vector<myCard> vecTmp;
		for(unsigned int uj=0;uj!=vecRes[ui].size();uj++) {
			vecTmp.push_back(vecCards[vecRes[ui][uj]]);
		}
		vecCardsArr.push_back(vecTmp);
	}
	unsigned int uiWinIdx = 0;
	int iWinHand = 0;
	compareXHands(vecCardsArr, uiWinIdx, iWinHand);
	
	if(uiWinIdx < vecCardsArr.size()) {
		vecWinCards.assign(vecCardsArr[uiWinIdx].begin(), vecCardsArr[uiWinIdx].end());
		return iWinHand;
	}
	else {
		cout << "---error: [getHandInX]a invalid uiWinIdx:" << uiWinIdx << ",CardsArrSz:" << vecCardsArr.size() << "---" << endl;
		return 0;
	}
}

//模拟发5张牌 
void myPokerTestA() {
    cout << "---###---func myPokerTestA() start---" << endl;
	
	myPoker oPoker(52);
    oPoker.shuffle(time(NULL));
    unsigned int i=0;
    cout << "---starting hand---" << endl;
    i++;oPoker.prtCardByIdx(i);i++;oPoker.prtCardByIdx(i);
    cout << "---flop---" << endl;
    i++;  //cut
	i++;oPoker.prtCardByIdx(i);i++;oPoker.prtCardByIdx(i);i++;oPoker.prtCardByIdx(i);
    cout << "---turn---" << endl;
    i++;  //cut
	i++;oPoker.prtCardByIdx(i);
    cout << "---river---" << endl;
    i++;  //cut
	i++;oPoker.prtCardByIdx(i);
	
    cout << "---###---func myPokerTestA() end---" << endl;
    system("PAUSE");
    return;
}

//测试牌型判定单个函数 
void myPokerTestB() {
    cout << "---###---func myPokerTestB() end---" << endl;
	
	vector<myCard> vec;
    myCard oCard1(10,"c");vec.push_back(oCard1);
    myCard oCard2(11,"c");vec.push_back(oCard2);
    myCard oCard3(9,"c");vec.push_back(oCard3);
    myCard oCard4(13,"c");vec.push_back(oCard4);
    myCard oCard5(12,"c");vec.push_back(oCard5);
	prtCards(vec);
	
	int iTJQKA = 0;
	if(isRoyalStraightFlush(vec)) {
        cout << "---RoyalStraightFlush---" << endl;
    }
	if(isStraightFlush(vec, iTJQKA)) {
        cout << "---StraightFlush---" << endl;
    }
	if(isFourOfAKind(vec)) {
        cout << "---FourOfAKind---" << endl;
    }
	if(isFullHouse(vec)) {
        cout << "---FullHouse---" << endl;
    }
	if(isFlush(vec)) {
        cout << "---Flush---" << endl;
    }
    if(isStraight(vec, iTJQKA)) {
        cout << "---Straight---" << endl;
    }
	if(isThreeOfAKind(vec)) {
        cout << "---ThreeOfAKind---" << endl;
    }
	if(isTwoPairs(vec)) {
        cout << "---TwoPairs---" << endl;
    }
	if(isOnePair(vec)) {
        cout << "---OnePair---" << endl;
    }
    
    cout << "---###---func myPokerTestB() end---" << endl;
    system("PAUSE");
    return;
}

//统计各个牌型出现的次数
void myPokerTestC() {
    cout << "---###---func myPokerTestC() start---" << endl;
	
	myPoker oPoker(52);
    vector<myCard> vec;
	int iRoyalStraightFlushCnt = 0;
	int iStraightFlushCnt = 0;
	int iFourOfAKindCnt = 0;
	int iFullHouseCnt = 0;
	int iFlushCnt = 0;
	int iStraightCnt = 0;
	int iThreeOfAKindCnt = 0;
	int iTwoPairsCnt = 0;
	int iOnePairCnt = 0;
	int iHighHandCnt = 0;
	int iX = 10000;
	int iY = 100;  //应该 大大小于'MAX_RAND' 同一轮内(同一iX下循环iY次)不能一直使用shuffle函数返回的rand序列作为种子
	int iPerFlag = 1;
	
	unsigned int uiSeed = time(NULL);
	for(int i=0;i<iX;i++) {
		Sleep(100);  //ms  每一轮sleep一下 防止cpu过高
		if(i%15 == 0) {  //每15*100ms 换种子 不再采用shuffle函数返回的rand序列
			uiSeed = time(NULL);
			if((i*100/iX>=90 && iPerFlag==9) || (i*100/iX>=80 && iPerFlag==8) || (i*100/iX>=70 && iPerFlag==7) || 
			   (i*100/iX>=60 && iPerFlag==6) || (i*100/iX>=50 && iPerFlag==5) || (i*100/iX>=40 && iPerFlag==4) || 
			   (i*100/iX>=30 && iPerFlag==3) || (i*100/iX>=20 && iPerFlag==2) || (i*100/iX>=10 && iPerFlag==1)) {
				iPerFlag++;
				cout << "===" << i*100/iX << "%===" << endl;
			}
		}
		for(int j=1;j<=iY;j++) {
			uiSeed = oPoker.shuffle(uiSeed);  //每次洗牌都换种子(shuffle函数返回的rand序列) 如果是固定种子(同一time(NULL)下循环)则洗牌序列相同 多次洗牌会导致牌被洗回原样(导致所出现的牌型固定有N种)
			oPoker.get5Cards(vec);
			int iTJQKA = 0;
			if(isRoyalStraightFlush(vec)) {
				iRoyalStraightFlushCnt++;
				//cout << "---RoyalStraightFlush---" << endl;
			}
			else if(isStraightFlush(vec, iTJQKA)) {  //iTJQKA must equal 0
				iStraightFlushCnt++;
				//cout << "---StraightFlush---" << endl;
			}
			else if(isFourOfAKind(vec)) {
				iFourOfAKindCnt++;
				//cout << "---FourOfAKind---" << endl;
			}
			else if(isFullHouse(vec)) {
				iFullHouseCnt++;
				//cout << "---FullHouse---" << endl;
			}
			else if(isFlush(vec)) {
				iFlushCnt++;
				//cout << "---Flush---" << endl;
			}
			else if(isStraight(vec, iTJQKA)) {
				iStraightCnt++;
				//cout << "---Straight---" << endl;
			}
			else if(isThreeOfAKind(vec)) {
				iThreeOfAKindCnt++;
				//cout << "---ThreeOfAKind---" << endl;
			}
			else if(isTwoPairs(vec)) {
				iTwoPairsCnt++;
				//cout << "---TwoPairs---" << endl;
			}
			else if(isOnePair(vec)) {
				iOnePairCnt++;
				//cout << "---OnePair---" << endl;
			}
			else {
				iHighHandCnt++;
				//cout << "---HighHand---" << endl;
			}
		}
    }
	
	int iTotalCnt = iX*iY;
	cout << "---Total: " << iTotalCnt << "---" << endl;
	cout << "---RoyalStraightFlush: " << iRoyalStraightFlushCnt << "/" << iTotalCnt << "=" << iRoyalStraightFlushCnt*1.0/iTotalCnt << endl;
	cout << "---     StraightFlush: " << iStraightFlushCnt << "/" << iTotalCnt << "=" << iStraightFlushCnt*1.0/iTotalCnt << endl;
	cout << "---       FourOfAKind: " << iFourOfAKindCnt << "/" << iTotalCnt << "=" << iFourOfAKindCnt*1.0/iTotalCnt << endl;
	cout << "---         FullHouse: " << iFullHouseCnt << "/" << iTotalCnt << "=" << iFullHouseCnt*1.0/iTotalCnt << endl;
	cout << "---             Flush: " << iFlushCnt << "/" << iTotalCnt << "=" << iFlushCnt*1.0/iTotalCnt << endl;
	cout << "---          Straight: " << iStraightCnt << "/" << iTotalCnt << "=" << iStraightCnt*1.0/iTotalCnt << endl;
	cout << "---      ThreeOfAKind: " << iThreeOfAKindCnt << "/" << iTotalCnt << "=" << iThreeOfAKindCnt*1.0/iTotalCnt << endl;
	cout << "---          TwoPairs: " << iTwoPairsCnt << "/" << iTotalCnt << "=" << iTwoPairsCnt*1.0/iTotalCnt << endl;
	cout << "---           OnePair: " << iOnePairCnt << "/" << iTotalCnt << "=" << iOnePairCnt*1.0/iTotalCnt << endl;
	cout << "---          HighHand: " << iHighHandCnt << "/" << iTotalCnt << "=" << iHighHandCnt*1.0/iTotalCnt << endl;
	
    cout << "---###---func myPokerTestC() end---" << endl;
    system("PAUSE");
    return;
}

//测试牌型计算函数&2个牌型比较函数
void myPokerTestD() {
    cout << "---###---func myPokerTestD() end---" << endl;
	
	//-------指定牌型-------
	/*
	int ret = 0;
	int iWinH = 0;
	vector<myCard> vecC_A;
    myCard oCard1_A(5,"c");vecC_A.push_back(oCard1_A);
    myCard oCard2_A(2,"c");vecC_A.push_back(oCard2_A);
    myCard oCard3_A(7,"c");vecC_A.push_back(oCard3_A);
    myCard oCard4_A(2,"s");vecC_A.push_back(oCard4_A);
    myCard oCard5_A(5,"h");vecC_A.push_back(oCard5_A);
	prtCards(vecC_A);
	vector<int> vecF_A;
	ret = getHand(vecC_A, vecF_A);
	cout << oTexasHands.getTexasHands(ret) << "=" << vecF_A[0] << "|" << vecF_A[1] << "|" << vecF_A[2] << "|" << vecF_A[3] << "|" << vecF_A[4] << endl;
	vector<myCard> vecC_B;
    myCard oCard1_B(5,"c");vecC_B.push_back(oCard1_B);
    myCard oCard2_B(2,"c");vecC_B.push_back(oCard2_B);
    myCard oCard3_B(7,"c");vecC_B.push_back(oCard3_B);
    myCard oCard4_B(2,"s");vecC_B.push_back(oCard4_B);
    myCard oCard5_B(5,"h");vecC_B.push_back(oCard5_B);
	prtCards(vecC_B);
	vector<int> vecF_B;
	ret = getHand(vecC_B, vecF_B);
	cout << oTexasHands.getTexasHands(ret) << "=" << vecF_B[0] << "|" << vecF_B[1] << "|" << vecF_B[2] << "|" << vecF_B[3] << "|" << vecF_B[4] << endl;
	
	ret = compare2Hands(vecC_A, vecC_B, iWinH);
	if(ret == 1) {cout << "===[A<B]===" << endl;}
	else if(ret == 2) {cout << "===[A>B]===" << endl;}
	else if(ret == 0) {cout << "===[A=B]===" << endl;}
	else {cout << "===myPokerTestD error-A===" << endl;}
	*/
	//-------指定牌型-------
	
	//-------随机牌型-------
	myPoker oPoker(52);
	vector<myCard> vecC_r_A;
	vector<int> vecF_r_A;
	vector<myCard> vecC_r_B;
	vector<int> vecF_r_B;
	int ret_r = 0;
	int iWinH_r = 0;
	int iX = 1;
	int iY = 5;  //应该 大大小于'MAX_RAND' 同一轮内(同一iX下循环iY次)不能一直使用shuffle函数返回的rand序列作为种子
	
	unsigned int uiSeed = time(NULL);
	for(int i=0;i<iX;i++) {
		Sleep(100);  //ms  每一轮sleep一下 防止cpu过高
		if(i%15 == 0) {  //每15*100ms 换种子 不再采用shuffle函数返回的rand序列
			uiSeed = time(NULL);
		}
		for(int j=1;j<=iY;j++) {
			uiSeed = oPoker.shuffle(uiSeed);  //每次洗牌都换种子(shuffle函数返回的rand序列) 如果是固定种子(同一time(NULL)下循环)则洗牌序列相同 多次洗牌会导致牌被洗回原样(导致所出现的牌型固定有N种)
			oPoker.get5Cards(vecC_r_A);
			prtCards(vecC_r_A);
			ret_r = getHand(vecC_r_A, vecF_r_A);
			cout << oTexasHands.getTexasHands(ret_r) << "=" << vecF_r_A[0] << "|" << vecF_r_A[1] << "|" << vecF_r_A[2] << "|" << vecF_r_A[3] << "|" << vecF_r_A[4] << endl;
			
			uiSeed = oPoker.shuffle(uiSeed);  //每次洗牌都换种子(shuffle函数返回的rand序列) 如果是固定种子(同一time(NULL)下循环)则洗牌序列相同 多次洗牌会导致牌被洗回原样(导致所出现的牌型固定有N种)
			oPoker.get5Cards(vecC_r_B);
			prtCards(vecC_r_B);
			ret_r = getHand(vecC_r_B, vecF_r_B);
			cout << oTexasHands.getTexasHands(ret_r) << "=" << vecF_r_B[0] << "|" << vecF_r_B[1] << "|" << vecF_r_B[2] << "|" << vecF_r_B[3] << "|" << vecF_r_B[4] << endl;
			
			ret_r = compare2Hands(vecC_r_A, vecC_r_B, iWinH_r);
			if(ret_r == 1) {cout << "===[A<B]===" << endl;}
			else if(ret_r == 2) {cout << "===[A>B]===" << endl;}
			else if(ret_r == 0) {cout << "===[A=B]===" << endl;}
			else {cout << "===myPokerTestD error-B===" << endl;}
		}
	}
	//-------随机牌型-------
    
    cout << "---###---func myPokerTestD() end---" << endl;
    system("PAUSE");
    return;
}

//模拟一轮完整比赛
#define TEST_E_PLAYER 6
void myPokerTestE() {
	cout << "---###---func myPokerTestE() start---" << endl;
	
	myPoker oPoker(52);
    oPoker.shuffle(time(NULL));
	
	unsigned int uiPlayerCnt = TEST_E_PLAYER;  // 2<=uiPlayerCnt<=10
	vector< vector<myCard> > vecPlayerCards;
	vecPlayerCards.resize(uiPlayerCnt);
	
	myCard oTmpCard;
	//Holecards
	for(unsigned int ui=0;ui<2;ui++) {
		for(unsigned int uj=0;uj<uiPlayerCnt;uj++) {
			oPoker.getCardByIdx(ui*uiPlayerCnt+uj+1, oTmpCard);
			vecPlayerCards[uj].push_back(oTmpCard);
			if(ui == 1) { //2张手牌发完
				cout << "---player " << uj+1 << ":" << endl;
				prtCards(vecPlayerCards[uj]);
			}
		}
	}
	//Communitycards
	vector<myCard> vecCCards;
	//cut;flop
	oPoker.getCardByIdx(2*uiPlayerCnt+2, oTmpCard);vecCCards.push_back(oTmpCard);
	oPoker.getCardByIdx(2*uiPlayerCnt+3, oTmpCard);vecCCards.push_back(oTmpCard);
	oPoker.getCardByIdx(2*uiPlayerCnt+4, oTmpCard);vecCCards.push_back(oTmpCard);
	//cut;turn
	oPoker.getCardByIdx(2*uiPlayerCnt+6, oTmpCard);vecCCards.push_back(oTmpCard);
	//cut;river
	oPoker.getCardByIdx(2*uiPlayerCnt+8, oTmpCard);vecCCards.push_back(oTmpCard);
	cout << "---Communitycards:" << endl;
	prtCards(vecCCards);
	
	int iWinHand = 0;
	vector<myCard> vecWinCards;
	vector<unsigned int> vecWinPlayerIdx;  //idx值由1开始
	int iTmpHand = 0;
	vector<myCard> vecTmpCards;
	for(unsigned int uk=1;uk<=uiPlayerCnt;uk++) {
		vecPlayerCards[uk-1].insert(vecPlayerCards[uk-1].end(), vecCCards.begin(), vecCCards.end());
		iTmpHand = getHandInX(vecPlayerCards[uk-1], vecTmpCards);
		cout << "---player " << uk << ":" << oTexasHands.getTexasHands(iTmpHand) << endl;
		prtCards(vecTmpCards);
		if(iTmpHand == 0) {
			cout << "===myPokerTestE error-A===" << endl;
			return;
		}
		if(iTmpHand > iWinHand) {
			iWinHand = iTmpHand;
			vecWinCards.assign(vecTmpCards.begin(), vecTmpCards.end());
			vecWinPlayerIdx.resize(1);
			vecWinPlayerIdx[0] = uk;
		}
		else if(iTmpHand == iWinHand) {
			int ret = compare2Hands(vecWinCards, vecTmpCards, iWinHand);
			if(ret == 1) {
				vecWinCards.assign(vecTmpCards.begin(), vecTmpCards.end());
				vecWinPlayerIdx.resize(1);
				vecWinPlayerIdx[0] = uk;
			}
			else if(ret == 2) {
				continue;
			}
			else if(ret == 0) {
				vecWinPlayerIdx.push_back(uk);
			}
			else {
				cout << "===myPokerTestE error-B===" << endl;
				return;
			}
		}
		else {
			continue;
		}
	}
	
	for(unsigned int ux=0;ux!=vecWinPlayerIdx.size();ux++) {cout << "winner is player:" << vecWinPlayerIdx[ux] << endl;}
	
    cout << "---###---func myPokerTestE() end---" << endl;
    system("PAUSE");
    return;
}

//统计获胜牌型的比例
#define TEST_F_PLAYER 6
void myPokerTestF() {
	cout << "---###---func myPokerTestF() start---" << endl;
	
	myPoker oPoker(52);
	unsigned int uiPlayerCnt = TEST_F_PLAYER;  // 2<=uiPlayerCnt<=10
	vector< vector<myCard> > vecPlayerCards;
	myCard oTmpCard;
	vector<myCard> vecCCards;
	int iWinHand = 0;
	vector<myCard> vecWinCards;
	vector<unsigned int> vecWinPlayerIdx;  //idx值由1开始
	int iTmpHand = 0;
	vector<myCard> vecTmpCards;
	
	int iRoyalStraightFlushCnt = 0;
	int iStraightFlushCnt = 0;
	int iFourOfAKindCnt = 0;
	int iFullHouseCnt = 0;
	int iFlushCnt = 0;
	int iStraightCnt = 0;
	int iThreeOfAKindCnt = 0;
	int iTwoPairsCnt = 0;
	int iOnePairCnt = 0;
	int iHighHandCnt = 0;
	int iX = 10000;
	int iY = 100;  //应该 大大小于'MAX_RAND' 同一轮内(同一iX下循环iY次)不能一直使用shuffle函数返回的rand序列作为种子
	int iPerFlag = 1;
	
	unsigned int uiSeed = time(NULL);
	for(int i=0;i<iX;i++) {
		Sleep(100);  //ms  每一轮sleep一下 防止cpu过高
		if(i%15 == 0) {  //每15*100ms 换种子 不再采用shuffle函数返回的rand序列
			uiSeed = time(NULL);
			if((i*100/iX>=90 && iPerFlag==9) || (i*100/iX>=80 && iPerFlag==8) || (i*100/iX>=70 && iPerFlag==7) || 
			   (i*100/iX>=60 && iPerFlag==6) || (i*100/iX>=50 && iPerFlag==5) || (i*100/iX>=40 && iPerFlag==4) || 
			   (i*100/iX>=30 && iPerFlag==3) || (i*100/iX>=20 && iPerFlag==2) || (i*100/iX>=10 && iPerFlag==1)) {
				iPerFlag++;
				cout << "===" << i*100/iX << "%===" << endl;
			}
		}
		for(int j=1;j<=iY;j++) {
			uiSeed = oPoker.shuffle(uiSeed);  //每次洗牌都换种子(shuffle函数返回的rand序列) 如果是固定种子(同一time(NULL)下循环)则洗牌序列相同 多次洗牌会导致牌被洗回原样(导致所出现的牌型固定有N种)
			
			vecPlayerCards.clear();
			vecPlayerCards.resize(uiPlayerCnt);
			//Holecards
			for(unsigned int ui=0;ui<2;ui++) {
				for(unsigned int uj=0;uj<uiPlayerCnt;uj++) {
					oPoker.getCardByIdx(ui*uiPlayerCnt+uj+1, oTmpCard);
					vecPlayerCards[uj].push_back(oTmpCard);
					/* if(ui == 1) { //2张手牌发完
						cout << "---player " << uj+1 << ":" << endl;
						prtCards(vecPlayerCards[uj]);
					} */
				}
			}
			//Communitycards
			vecCCards.clear();
			//cut;flop
			oPoker.getCardByIdx(2*uiPlayerCnt+2, oTmpCard);vecCCards.push_back(oTmpCard);
			oPoker.getCardByIdx(2*uiPlayerCnt+3, oTmpCard);vecCCards.push_back(oTmpCard);
			oPoker.getCardByIdx(2*uiPlayerCnt+4, oTmpCard);vecCCards.push_back(oTmpCard);
			//cut;turn
			oPoker.getCardByIdx(2*uiPlayerCnt+6, oTmpCard);vecCCards.push_back(oTmpCard);
			//cut;river
			oPoker.getCardByIdx(2*uiPlayerCnt+8, oTmpCard);vecCCards.push_back(oTmpCard);
			//cout << "---Communitycards:" << endl;
			//prtCards(vecCCards);
			
			iWinHand = 0;
			vecWinCards.clear();
			vecWinPlayerIdx.clear();  //idx值由1开始
			iTmpHand = 0;
			vecTmpCards.clear();
			for(unsigned int uk=1;uk<=uiPlayerCnt;uk++) {
				vecPlayerCards[uk-1].insert(vecPlayerCards[uk-1].end(), vecCCards.begin(), vecCCards.end());
				iTmpHand = getHandInX(vecPlayerCards[uk-1], vecTmpCards);
				//cout << "---player " << uk << ":" << oTexasHands.getTexasHands(iTmpHand) << endl;
				//prtCards(vecTmpCards);
				if(iTmpHand == 0) {
					cout << "===myPokerTestF error-A===" << endl;
					return;
				}
				if(iTmpHand > iWinHand) {
					iWinHand = iTmpHand;
					vecWinCards.assign(vecTmpCards.begin(), vecTmpCards.end());
					vecWinPlayerIdx.resize(1);
					vecWinPlayerIdx[0] = uk;
				}
				else if(iTmpHand == iWinHand) {
					int ret = compare2Hands(vecWinCards, vecTmpCards, iWinHand);
					if(ret == 1) {
						vecWinCards.assign(vecTmpCards.begin(), vecTmpCards.end());
						vecWinPlayerIdx.resize(1);
						vecWinPlayerIdx[0] = uk;
					}
					else if(ret == 2) {
						continue;
					}
					else if(ret == 0) {
						vecWinPlayerIdx.push_back(uk);
					}
					else {
						cout << "===myPokerTestF error-B===" << endl;
						return;
					}
				}
				else {
					continue;
				}
			}
			//for(unsigned int ux=0;ux!=vecWinPlayerIdx.size();ux++) {cout << "winner is player:" << vecWinPlayerIdx[ux] << endl;}
			
			if(iWinHand == ROYALSTRAIGHTFLUSH) {
				iRoyalStraightFlushCnt++;
				//cout << "---winner is RoyalStraightFlush---" << endl;
			}
			else if(iWinHand == STRAIGHTFLUSH) {
				iStraightFlushCnt++;
				//cout << "---winner is StraightFlush---" << endl;
			}
			else if(iWinHand == FOUROFAKIND) {
				iFourOfAKindCnt++;
				//cout << "---winner is FourOfAKind---" << endl;
			}
			else if(iWinHand == FULLHOUSE) {
				iFullHouseCnt++;
				//cout << "---winner is FullHouse---" << endl;
			}
			else if(iWinHand == FLUSH) {
				iFlushCnt++;
				//cout << "---winner is Flush---" << endl;
			}
			else if(iWinHand == STRAIGHT) {
				iStraightCnt++;
				//cout << "---winner is Straight---" << endl;
			}
			else if(iWinHand == THREEOFAKIND) {
				iThreeOfAKindCnt++;
				//cout << "---winner is ThreeOfAKind---" << endl;
			}
			else if(iWinHand == TWOPAIRS) {
				iTwoPairsCnt++;
				//cout << "---winner is TwoPairs---" << endl;
			}
			else if(iWinHand == ONEPAIR) {
				iOnePairCnt++;
				//cout << "---winner is OnePair---" << endl;
			}
			else if(iWinHand == HIGHHAND) {
				iHighHandCnt++;
				//cout << "---winner is HighHand---" << endl;
			}
			else {
				cout << "===myPokerTestF error-C===" << endl;
				return;
			}
		}
    }
	
	int iTotalCnt = iX*iY;
	cout << "---Total: " << iTotalCnt << "---" << endl;
	cout << "---RoyalStraightFlush: " << iRoyalStraightFlushCnt << "/" << iTotalCnt << "=" << iRoyalStraightFlushCnt*1.0/iTotalCnt << endl;
	cout << "---     StraightFlush: " << iStraightFlushCnt << "/" << iTotalCnt << "=" << iStraightFlushCnt*1.0/iTotalCnt << endl;
	cout << "---       FourOfAKind: " << iFourOfAKindCnt << "/" << iTotalCnt << "=" << iFourOfAKindCnt*1.0/iTotalCnt << endl;
	cout << "---         FullHouse: " << iFullHouseCnt << "/" << iTotalCnt << "=" << iFullHouseCnt*1.0/iTotalCnt << endl;
	cout << "---             Flush: " << iFlushCnt << "/" << iTotalCnt << "=" << iFlushCnt*1.0/iTotalCnt << endl;
	cout << "---          Straight: " << iStraightCnt << "/" << iTotalCnt << "=" << iStraightCnt*1.0/iTotalCnt << endl;
	cout << "---      ThreeOfAKind: " << iThreeOfAKindCnt << "/" << iTotalCnt << "=" << iThreeOfAKindCnt*1.0/iTotalCnt << endl;
	cout << "---          TwoPairs: " << iTwoPairsCnt << "/" << iTotalCnt << "=" << iTwoPairsCnt*1.0/iTotalCnt << endl;
	cout << "---           OnePair: " << iOnePairCnt << "/" << iTotalCnt << "=" << iOnePairCnt*1.0/iTotalCnt << endl;
	cout << "---          HighHand: " << iHighHandCnt << "/" << iTotalCnt << "=" << iHighHandCnt*1.0/iTotalCnt << endl;
	
	cout << "---###---func myPokerTestF() end---" << endl;
    system("PAUSE");
    return;
}

//统计调节参数后获胜牌型的比例
#define TEST_G_PLAYER 6
void myPokerTestG() {
	cout << "---###---func myPokerTestG() start---" << endl;
    cout << "---###---func myPokerTestG() end---" << endl;
    system("PAUSE");
    return;
}

int main(int argc, char *argv[])
{
      //testMysqlEscape();
	  //myFileOp();
	  
	  /* 处理电影ass字幕
	  map<string, string> mapAssFile;
	  mapAssFile["Breaking.Bad.S05E01.Live.Free.or.Die.720p.WEB-DL.DD5.1.H.264-CtrlHD.chs&eng"] = "Breaking Bad - S05E01 - Live Free or Die";
	  mapAssFile["Breaking.Bad.S05E02.Madrigal.720p.WEB-DL.DD5.1.H.264-CtrlHD.chs&eng"] = "Breaking Bad - S05E02 - Madrigal";
	  mapAssFile["Breaking.Bad.S05E03.Hazard.Pay.720p.WEB-DL.DD5.1.H.264-CtrlHD.chs&eng"] = "Breaking Bad - S05E03 - Hazard Pay";
	  mapAssFile["Breaking.Bad.S05E04.Fifty-One.720p.WEB-DL.DD5.1.H.264-CtrlHD.chs&eng"] = "Breaking Bad - S05E04 - Fifty-One";
	  mapAssFile["Breaking.Bad.S05E05.Dead.Freight.720p.WEB-DL.DD5.1.H.264-CtrlHD.chs&eng"] = "Breaking Bad - S05E05 - Dead Freight";
	  mapAssFile["Breaking.Bad.S05E06.Buyout.720p.WEB-DL.DD5.1.H.264-CtrlHD.chs&eng"] = "Breaking Bad - S05E06 - Buyout";
	  mapAssFile["Breaking.Bad.S05E07.Say.My.Name.720p.WEB-DL.DD5.1.H.264-CtrlHD.chs&eng"] = "Breaking Bad - S05E07 - Say My Name";
	  mapAssFile["Breaking.Bad.S05E08.Gliding.Over.All.720p.WEB-DL.DD5.1.H.264-CtrlHD.chs&eng"] = "Breaking Bad - S05E08 - Gliding Over All";
	  mapAssFile["Breaking.Bad.S05E09.Blood.Money.720p.WEB-DL.DD5.1.H.264-BS.chs&eng"] = "Breaking Bad - S05E09 - Blood Money";
	  mapAssFile["Breaking.Bad.S05E10.Buried.720p.WEB-DL.DD5.1.H.264-BS.chs&eng"] = "Breaking Bad - S05E10 - Buried";
	  mapAssFile["Breaking.Bad.S05E11.Confessions.720p.WEB-DL.DD5.1.H.264-BS.chs&eng"] = "Breaking Bad - S05E11 - Confessions";
	  mapAssFile["Breaking.Bad.S05E12.Rabid Dog.720p.WEB-DL.DD5.1.H.264-BS.chs&eng"] = "Breaking Bad - S05E12 - Rabid Dog";
	  mapAssFile["Breaking.Bad.S05E13.To'hajiilee.720p.WEB-DL.DD5.1.H.264-BS.chs&eng"] = "Breaking Bad - S05E13 - To'Hajiilee";
	  mapAssFile["Breaking.Bad.S05E14.Ozymandias.720p.WEB-DL.DD5.1.H.264-BS.chs&eng"] = "Breaking Bad - S05E14 - Ozymandias";
	  mapAssFile["Breaking.Bad.S05E15.Granite.Slate.720p.WEB-DL.DD5.1.H.264-BS.chs&eng"] = "Breaking Bad - S05E15 - Granite State";
	  mapAssFile["Breaking.Bad.S05E16.Felina.720p.WEB-DL.DD5.1.H.264-BS.chs&eng"] = "Breaking Bad - S05E16 - Felina";
	  for(map<string, string>::iterator it=mapAssFile.begin(); it!=mapAssFile.end(); it++) {
	      myAssFileOp(it->first, it->second, 1);
	  }
	  */
	  //myAssFileOp();
	  
	  /* 处理电影srt字幕
	  map<string, string> mapSrtFile;
	  mapSrtFile["the.wire.s02e01.dvdrip.xvid-ffndvd.chs"] = "The.Wire.S02E01.Ebb.Tide.720p.WEB-DL.DD5.1.H.264-NTb";
	  mapSrtFile["the.wire.s02e02.dvdrip.xvid-ffndvd.chs"] = "The.Wire.S02E02.Collateral.Damage.720p.WEB-DL.DD5.1.H.264-NTb";
	  mapSrtFile["the.wire.s02e03.dvdrip.xvid-ffndvd.chs"] = "The.Wire.S02E03.Hot.Shots.720p.WEB-DL.DD5.1.H.264-NTb";
	  mapSrtFile["the.wire.s02e04.dvdrip.xvid-ffndvd.chs"] = "The.Wire.S02E04.Hard.Cases.720p.WEB-DL.DD5.1.H.264-NTb";
	  mapSrtFile["the.wire.s02e05.dvdrip.xvid-ffndvd.chs"] = "The.Wire.S02E05.Undertow.720p.WEB-DL.DD5.1.H.264-NTb";
	  mapSrtFile["the.wire.s02e06.dvdrip.xvid-ffndvd.chs"] = "The.Wire.S02E06.All.Prologue.720p.WEB-DL.DD5.1.H.264-NTb";
	  mapSrtFile["the.wire.s02e07.dvdrip.xvid-ffndvd.chs"] = "The.Wire.S02E07.Backwash.720p.WEB-DL.DD5.1.H.264-NTb";
	  mapSrtFile["the.wire.s02e08.dvdrip.xvid-ffndvd.chs"] = "The.Wire.S02E08.Duck.and.Cover.720p.WEB-DL.DD5.1.H.264-NTb";
	  mapSrtFile["the.wire.s02e09.dvdrip.xvid-ffndvd.chs"] = "The.Wire.S02E09.Stray.Rounds.720p.WEB-DL.DD5.1.H.264-NTb";
	  mapSrtFile["the.wire.s02e10.dvdrip.xvid-ffndvd.chs"] = "The.Wire.S02E10.Storm.Warnings.720p.WEB-DL.DD5.1.H.264-NTb";
	  mapSrtFile["the.wire.s02e11.dvdrip.xvid-ffndvd.chs"] = "The.Wire.S02E11.Bad.Dreams.720p.WEB-DL.DD5.1.H.264-NTb";
	  mapSrtFile["the.wire.s02e12.dvdrip.xvid-ffndvd.chs"] = "The.Wire.S02E12.Port.in.a.Storm.720p.WEB-DL.DD5.1.H.264-NTb";
	  for(map<string, string>::iterator it=mapSrtFile.begin(); it!=mapSrtFile.end(); it++) {
	      mySrtFileOp(it->first, it->second, -1);
	  }
	  */
	  //mySrtFileOp();
	  
	  //myTime();
      
      //puzzleA();
	  
	  //CnA();
      
      //myPokerTestA();
      //myPokerTestB();
	  //myPokerTestC();
	  //myPokerTestD();
	  //for(int i=1;i<=10;i++){cout<<"Round-"<<i<<endl;myPokerTestE();}
	  //myPokerTestF();
      
    system("PAUSE");
    return EXIT_SUCCESS;
}
