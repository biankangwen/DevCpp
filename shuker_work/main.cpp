#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <windows.h>  //Sleep

#include "mysql_escape.h"

using namespace std;

void testMysqlEscape() {
  cout << "---###---func testMysqlEscape() start---";
  
  string a = "\'xx\"";
  string b = EscapeString2(a);
  printf("a:%s\n", a.c_str());
  printf("b:%s\n", b.c_str());
  
  cout << "---###---func testMysqlEscape() end---";
  system("PAUSE");
  return;
}

void myFileOp() {
  cout << "---###---func myFileOp() start---";
  
  ofstream ofile("a.txt",ios::app);
  ofile << "haha" << ":[" << 5 << "]" << endl;
  ofile.close();
  
  cout << "---###---func myFileOp() end---";
  system("PAUSE");
  return;
}

void myTime() {
     cout << "---###---func myTime() start---";
	 
	 time_t tTime = time(NULL);
     char szTime[16] = {0};
     strftime(szTime,sizeof(szTime),"%X",localtime(&tTime));
     printf("tTime:%u\nszTime:%s\n",tTime,szTime);
     
     cout << "---###---func myTime() end---";
     system("PAUSE");
     return;
}

void puzzleA() {
     cout << "---###---func puzzleA() start---";
	 
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
                 if(flag >1) {
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
     
     cout << "---###---func puzzleA() end---";
     system("PAUSE");
     return;
}

/*
 *Texas Hold'em Poker
 *皇家同花顺-Royal straight flush；同花顺-Straight flush；四条（金刚）-Four of a kind；葫芦-Full house(Boat)；
 *同花-Flush；顺子-Straight；三条-Three of a kind；两对-Two pairs；一对-One pair；高牌 -High hand
 *Suit:s=spade;h=heart;c=club;d=diamond;j=JOKER(red j;black j)
 */
class myCard {
public:
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
void prt5Card(vector<myCard> &vecCards) {
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
class texasHands {
public:
	texasHands() {
		mapHands[10] = "RoyalStraightFlush";
		mapHands[9] = "StraightFlush";
		mapHands[8] = "FourOfAKind";
		mapHands[7] = "FullHouse";
		mapHands[6] = "Flush";
		mapHands[5] = "Straight";
		mapHands[4] = "ThreeOfAKind";
		mapHands[3] = "TwoPairs";
		mapHands[2] = "OnePair";
		mapHands[1] = "HighHand";
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

/*计算牌型 采用'mapHands'的定义
 *并按可比较的点数降序排列 如3333K 22Q84
 *A=14 K=13 Q=12 J=11
 */
int getHand(vector<myCard> &vecCards, vector<int> &vecFigures) {
	if(vecCards.size() != 5) {
		cout << "---error: [getHand]a invalid cards num:" << vecCards.size() << "---" << endl;
		return 0;
	}
	
	vecFigures.clear();
	
	int iHand = 0;
	int iTJQKA = 0;
	if(isRoyalStraightFlush(vecCards)) {
		iHand = 10;
		//cout << "---RoyalStraightFlush---" << endl;
		vecFigures.push_back(14);
		vecFigures.push_back(13);
		vecFigures.push_back(12);
		vecFigures.push_back(11);
		vecFigures.push_back(10);
	}
	else if(isStraightFlush(vecCards, iTJQKA)) {  //iTJQKA must equal 0
		iHand = 9;
		//cout << "---StraightFlush---" << endl;
		vecFigures.push_back(vecCards[0].getFigure());
		vecFigures.push_back(vecCards[1].getFigure());
		vecFigures.push_back(vecCards[2].getFigure());
		vecFigures.push_back(vecCards[3].getFigure());
		vecFigures.push_back(vecCards[4].getFigure());
		sort(vecFigures.begin(), vecFigures.end(), greater<int>());
	}
	else if(isFourOfAKind(vecCards)) {
		iHand = 8;
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
			vecFigures.push_back(it->first);
			vecFigures.push_back(it->first);
			vecFigures.push_back(it->first);
			vecFigures.push_back(it->first);
			vecFigures.push_back((++it)->first);
		}
		else {
			vecFigures.push_back((++it)->first);
			vecFigures.push_back(it->first);
			vecFigures.push_back(it->first);
			vecFigures.push_back(it->first);
			vecFigures.push_back((--it)->first);
		}
	}
	else if(isFullHouse(vecCards)) {
		iHand = 7;
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
			vecFigures.push_back(it->first);
			vecFigures.push_back(it->first);
			vecFigures.push_back(it->first);
			vecFigures.push_back((++it)->first);
			vecFigures.push_back(it->first);
		}
		else {
			vecFigures.push_back((++it)->first);
			vecFigures.push_back(it->first);
			vecFigures.push_back(it->first);
			vecFigures.push_back((--it)->first);
			vecFigures.push_back(it->first);
		}
	}
	else if(isFlush(vecCards)) {
		iHand = 6;
		//cout << "---Flush---" << endl;
		vecFigures.push_back(vecCards[0].getFigure()==1?14:vecCards[0].getFigure());
		vecFigures.push_back(vecCards[1].getFigure()==1?14:vecCards[1].getFigure());
		vecFigures.push_back(vecCards[2].getFigure()==1?14:vecCards[2].getFigure());
		vecFigures.push_back(vecCards[3].getFigure()==1?14:vecCards[3].getFigure());
		vecFigures.push_back(vecCards[4].getFigure()==1?14:vecCards[4].getFigure());
		sort(vecFigures.begin(), vecFigures.end(), greater<int>());
	}
	else if(isStraight(vecCards, iTJQKA)) {
		iHand = 5;
		//cout << "---Straight---" << endl;
		if(iTJQKA) {
			vecFigures.push_back(14);
			vecFigures.push_back(13);
			vecFigures.push_back(12);
			vecFigures.push_back(11);
			vecFigures.push_back(10);
		}
		else {
			vecFigures.push_back(vecCards[0].getFigure());
			vecFigures.push_back(vecCards[1].getFigure());
			vecFigures.push_back(vecCards[2].getFigure());
			vecFigures.push_back(vecCards[3].getFigure());
			vecFigures.push_back(vecCards[4].getFigure());
			sort(vecFigures.begin(), vecFigures.end(), greater<int>());
		}
	}
	else if(isThreeOfAKind(vecCards)) {
		iHand = 4;
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
				vecFigures.push_back(it->first);
				vecFigures.push_back(it->first);
				vecFigures.push_back(it->first);
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
		vecFigures.push_back(fig_1_b);
		vecFigures.push_back(fig_1_s);
	}
	else if(isTwoPairs(vecCards)) {
		iHand = 3;
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
					vecFigures.push_back(it->first);
					vecFigures.push_back(it->first);
				}
			}
			else {
				fig_1 = it->first;
			}
		}
		vecFigures.push_back(fig_2);
		vecFigures.push_back(fig_2);
		vecFigures.push_back(fig_1);
	}
	else if(isOnePair(vecCards)) {
		iHand = 2;
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
				vecFigures.push_back(it->first);
				vecFigures.push_back(it->first);
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
		vecFigures.push_back(fig_1_b);
		vecFigures.push_back(fig_1_m);
		vecFigures.push_back(fig_1_s);
	}
	else {
		iHand = 1;
		//cout << "---HighHand---" << endl;
		vecFigures.push_back(vecCards[0].getFigure()==1?14:vecCards[0].getFigure());
		vecFigures.push_back(vecCards[1].getFigure()==1?14:vecCards[1].getFigure());
		vecFigures.push_back(vecCards[2].getFigure()==1?14:vecCards[2].getFigure());
		vecFigures.push_back(vecCards[3].getFigure()==1?14:vecCards[3].getFigure());
		vecFigures.push_back(vecCards[4].getFigure()==1?14:vecCards[4].getFigure());
		sort(vecFigures.begin(), vecFigures.end(), greater<int>());
	}
	
	return iHand;
}

//比较牌型大小 -1:error 0:A=B 1:A<B 2:A>B
int compareHands(vector<myCard> &vecCards_A, vector<myCard> &vecCards_B) {
	if(vecCards_A.size()!=5 || vecCards_B.size()!=5) {
		cout << "---error: [compareHands]a invalid cards num:" << vecCards_A.size() << "|" << vecCards_B.size() << "---" << endl;
		return -1;
	}
	
	int iHand_A = 0;
	int iHand_B = 0;
	vector<int> vecFigures_A;
	vector<int> vecFigures_B;
	iHand_A = getHand(vecCards_A, vecFigures_A);
	iHand_B = getHand(vecCards_B, vecFigures_B);
	if(iHand_A==0 || iHand_B==0 || vecFigures_A.size()!=5 || vecFigures_B.size()!=5) {
		cout << "---error: [compareHands]a invalid getHand ret:" << iHand_A << "|" << iHand_B << "; vecF_sz:" << vecFigures_A.size() << vecFigures_B.size() << "---" << endl;
		return -1;
	}
	
	if(iHand_A > iHand_B) {
		return 2;
	}
	else if(iHand_A < iHand_B) {
		return 1;
	}
	else {
		for(int i=0;i<5;i++) {
			if(vecFigures_A[i] > vecFigures_B[i]) {
				return 2;
			}
			else if(vecFigures_A[i] < vecFigures_B[i]) {
				return 1;
			}
			else {
				continue;
			}
		}
		return 0;
	}
}

//模拟发牌 
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
    cout << "---###---func myPokerTestC() end---" << endl;
	
	vector<myCard> vec;
    myCard oCard1(10,"c");vec.push_back(oCard1);
    myCard oCard2(11,"c");vec.push_back(oCard2);
    myCard oCard3(9,"c");vec.push_back(oCard3);
    myCard oCard4(13,"c");vec.push_back(oCard4);
    myCard oCard5(12,"c");vec.push_back(oCard5);
	prt5Card(vec);
	
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
    
    cout << "---###---func myPokerTestC() end---" << endl;
    system("PAUSE");
    return;
}

//统计各个牌型出现的次数
void myPokerTestC() {
    cout << "---###---func myPokerTestB() start---" << endl;
	
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
	
	unsigned int uiSeed = time(NULL);
	for(int i=0;i<iX;i++) {
		Sleep(100);  //ms  每一轮sleep一下 防止cpu过高
		if(i%15 == 0) {  //每15*100ms 换种子 不再采用shuffle函数返回的rand序列
			uiSeed = time(NULL);
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
	
    cout << "---###---func myPokerTestB() end---" << endl;
    system("PAUSE");
    return;
}

//测试牌型计算函数
void myPokerTestD() {
    cout << "---###---func myPokerTestD() end---" << endl;
	
	//-------指定牌型-------
	/* vector<myCard> vecC;
    myCard oCard1(5,"c");vecC.push_back(oCard1);
    myCard oCard2(2,"c");vecC.push_back(oCard2);
    myCard oCard3(7,"c");vecC.push_back(oCard3);
    myCard oCard4(2,"s");vecC.push_back(oCard4);
    myCard oCard5(5,"h");vecC.push_back(oCard5);
	prt5Card(vecC);
	vector<int> vecF;
	int ret = getHand(vecC, vecF);
	cout << oTexasHands.getTexasHands(ret) << "=" << vecF[0] << "|" << vecF[1] << "|" << vecF[2] << "|" << vecF[3] << "|" << vecF[4] << endl; */
	//-------指定牌型-------
	
	//-------随机牌型-------
	myPoker oPoker(52);
	vector<myCard> vecC_r;
	vector<int> vecF_r;
	int ret_r = 0;
	int iX = 1;
	int iY = 3;  //应该 大大小于'MAX_RAND' 同一轮内(同一iX下循环iY次)不能一直使用shuffle函数返回的rand序列作为种子
	
	unsigned int uiSeed = time(NULL);
	for(int i=0;i<iX;i++) {
		Sleep(100);  //ms  每一轮sleep一下 防止cpu过高
		if(i%15 == 0) {  //每15*100ms 换种子 不再采用shuffle函数返回的rand序列
			uiSeed = time(NULL);
		}
		for(int j=1;j<=iY;j++) {
			uiSeed = oPoker.shuffle(uiSeed);  //每次洗牌都换种子(shuffle函数返回的rand序列) 如果是固定种子(同一time(NULL)下循环)则洗牌序列相同 多次洗牌会导致牌被洗回原样(导致所出现的牌型固定有N种)
			oPoker.get5Cards(vecC_r);
			prt5Card(vecC_r);
			ret_r = getHand(vecC_r, vecF_r);
			cout << oTexasHands.getTexasHands(ret_r) << "=" << vecF_r[0] << "|" << vecF_r[1] << "|" << vecF_r[2] << "|" << vecF_r[3] << "|" << vecF_r[4] << endl;
		}
	}
	//-------随机牌型-------
    
    cout << "---###---func myPokerTestD() end---" << endl;
    system("PAUSE");
    return;
}

//测试牌型比较函数
void myPokerTestE() {
    cout << "---###---func myPokerTestE() end---" << endl;
	
	
    
    cout << "---###---func myPokerTestE() end---" << endl;
    system("PAUSE");
    return;
}

int main(int argc, char *argv[])
{
      //testMysqlEscape();
	  //myFileOp();
	  //myTime();
      
      //puzzleA();
      
      //myPokerTestA();
      //myPokerTestB();
	  //myPokerTestC();
	  myPokerTestD();
	  //myPokerTestE();
      
    system("PAUSE");
    return EXIT_SUCCESS;
}
