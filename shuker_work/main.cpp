#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <windows.h>  //Sleep

#include "mysql_escape.h"

using namespace std;

void testMysqlEscape() {
  string a = "\'xx\"";
  string b = EscapeString2(a);
  printf("a:%s\n", a.c_str());
  printf("b:%s\n", b.c_str());
  
  cout << "---func testMysqlEscape() end---";
  system("PAUSE");
  return;
}

void myFileOp() {
  ofstream ofile("a.txt",ios::app);
  ofile << "haha" << ":[" << 5 << "]" << endl;
  ofile.close();
  return;
}

void myTime() {
     time_t tTime = time(NULL);
     char szTime[16] = {0};
     strftime(szTime,sizeof(szTime),"%X",localtime(&tTime));
     printf("tTime:%u\nszTime:%s\n",tTime,szTime);
     
     cout << "---func myTime() end---";
     system("PAUSE");
     return;
}

void puzzleA() {
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
     
     cout << "---func puzzleA() end---";
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
      
	  //uiIdx-从1起
      void getCard(unsigned int uiIdx, bool bIdx=false) {
           if(uiIdx>vecCards.size() || uiIdx==0) {
                cout << "---error: this is a invalid card idx---" << endl;
                return;
           }
           if(bIdx) {
               cout << vecCards[uiIdx-1].prtCard() << ":[" << uiIdx << "]" << endl;
           }
           else {
               cout << vecCards[uiIdx-1].prtCard() << endl;
           }
           return;
      }
      
      unsigned int getCardNum() {
          return vecCards.size();
      }
      
      void get5Cards(vector<myCard> &vec) {
           vec.assign(vecCards.begin(), vecCards.begin()+5);
           return;
      }

private:
      vector<myCard> vecCards;
};

bool isFlush(vector<myCard> &vecCards) {
     if(vecCards.size() != 5) {
         cout << "---error: [isFlush]a invalid cards num" << vecCards.size() << "---" << endl;
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
         cout << "---error: [isStraight]a invalid cards num" << vecCards.size() << "---" << endl;
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
         cout << "---error: [isStraightFlush]a invalid cards num" << vecCards.size() << "---" << endl;
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
         cout << "---error: [isRoyalStraightFlush]a invalid cards num" << vecCards.size() << "---" << endl;
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
		cout << "---error: [isFourOfAKind]a invalid cards num" << vecCards.size() << "---" << endl;
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
		cout << "---error: [isFullHouse]a invalid cards num" << vecCards.size() << "---" << endl;
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
		cout << "---error: [isThreeOfAKind]a invalid cards num" << vecCards.size() << "---" << endl;
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
		cout << "---error: [isTwoPairs]a invalid cards num" << vecCards.size() << "---" << endl;
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
		cout << "---error: [isOnePair]a invalid cards num" << vecCards.size() << "---" << endl;
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
	if(mapFigureCnt.size() == 4) {
		return true;
	}
	else {
		return false;
	}
}

//按点数降序排列
void getHighHand(vector<myCard> &vecCards) {
}

//模拟发牌 
void myPokerTestA() {
    myPoker oPoker(52);
    oPoker.shuffle(time(NULL));
    unsigned int i=0;
    cout << "---starting hand---" << endl;
    i++;oPoker.getCard(i);i++;oPoker.getCard(i);
    cout << "---flop---" << endl;
    i++;  //cut
	i++;oPoker.getCard(i);i++;oPoker.getCard(i);i++;oPoker.getCard(i);
    cout << "---turn---" << endl;
    i++;  //cut
	i++;oPoker.getCard(i);
    cout << "---river---" << endl;
    i++;  //cut
	i++;oPoker.getCard(i);
    cout << "---func myPokerTestA() end---" << endl;
    system("PAUSE");
    return;
}

void myPokerTestB() {
    myPoker oPoker(52);
    vector<myCard> vec;
	unsigned int uiSeed = time(NULL);
	for(int i=0;i<5;i++) {
		for(int j=1;j<=100;j++) {  //每一轮sleep一下
			uiSeed = oPoker.shuffle(uiSeed);  //每次洗牌都换种子 如果是固定种子则洗牌序列相同 多次洗牌会导致牌被洗回原样(导致所出现的牌型固定有N种)
			oPoker.get5Cards(vec);
			int iTJQKA = 0;
			if(isStraight(vec, iTJQKA)) {
				cout << "---straight---:" << i*100+j << endl;
				for(unsigned int ui=0;ui<vec.size();ui++) {
					cout << vec[ui].prtCard() << endl;
				}
				cout << "------" << endl;
			}
			if(isFlush(vec)) {
				cout << "---flush---:" << i*100+j << endl;
				for(unsigned int ui=0;ui<vec.size();ui++) {
					cout << vec[ui].prtCard() << endl;
				}
				cout << "------" << endl;
			}
		}
		Sleep(100);  //ms
    }
    cout << "---func myPokerTestB() end---" << endl;
    system("PAUSE");
    return;
}

//测试牌型判定单个函数 
void myPokerTestC() {
    vector<myCard> vec;
    myCard oCard1(5,"c");vec.push_back(oCard1);
    myCard oCard2(3,"h");vec.push_back(oCard2);
    myCard oCard3(7,"s");vec.push_back(oCard3);
    myCard oCard4(1,"c");vec.push_back(oCard4);
    myCard oCard5(10,"d");vec.push_back(oCard5);
	for(unsigned int ui=0;ui<vec.size();ui++) {
		cout << vec[ui].prtCard() << endl;
	}
	int iTJQKA = 0;
    if(isStraight(vec, iTJQKA)) {
        cout << "---Straight---" << endl;
    }
    if(isFlush(vec)) {
        cout << "---Flush---" << endl;
    }
	if(isStraightFlush(vec, iTJQKA)) {
        cout << "---StraightFlush---" << endl;
    }
	if(isRoyalStraightFlush(vec)) {
        cout << "---RoyalStraightFlush---" << endl;
    }
	if(isFourOfAKind(vec)) {
        cout << "---FourOfAKind---" << endl;
    }
	if(isFullHouse(vec)) {
        cout << "---FullHouse---" << endl;
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
    
    cout << "---func myPokerTestC() end---" << endl;
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
	  
	  myPokerTestC();
      
    system("PAUSE");
    return EXIT_SUCCESS;
}
