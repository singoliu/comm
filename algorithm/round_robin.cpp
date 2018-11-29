#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>

using namespace std;
  
class Server
{    
private:
    std::string m_sIp; 
    int m_iWeight;    

public:
    Server(string ip, int weight) 
    {    
         this->m_sIp = ip;    
         this->m_iWeight = weight;    
    }  

    string GetIp() 
    {  
        return m_sIp;  
    }  

    void setIp(string ip) 
    {  
        this->m_sIp = ip;  
    }  

    int GetWeight() 
    {  
        return m_iWeight;  
    }  

    void SetWeight(int weight) 
    {  
        this->m_iWeight = weight;  
    } 
 };




class WeightRoundRobin 
{  
      
    
private:
    int m_iCurrentIndex;   //**上次选择的服务器 
    
    int m_iCurrentWeight; //**当前调度的权值     
    
    int m_iMaxWeight;   //**最大权重    
    
    int m_iGcdWeight;   //**权重的最大公约数 
    
    int m_iSvrCount;  //**服务器数    
    
    std::vector<Server> m_lServer;   
      
public : 
    WeightRoundRobin():m_iCurrentIndex(-1),m_iCurrentWeight(0),m_iMaxWeight(0),m_iGcdWeight(0),m_iSvrCount(0)
        {}

    void Show()
    {
        printf("m_iCurrentIndex=%d;m_iCurrentWeight=%d;m_lServer[%d].GetWeight()=%d\n",
            m_iCurrentIndex,m_iCurrentWeight,m_iCurrentIndex,m_lServer[m_iCurrentIndex].GetWeight());
    }
    
     //* 得到两值的最大公约数  
    int greaterCommonDivisor(int a, int b)
    {    
        if(a % b == 0)
        {  
            return b;  
        }
        else
        {  
            return greaterCommonDivisor(b,a % b);  
        }  
    } 
    

     //得到list中所有权重的最大公约数，实际上是两两取最大公约数d，然后得到的d 
     //与下一个权重取最大公约数，直至遍历完      
    int greatestCommonDivisor(std::vector<Server>& lServer)
    {    
        int divisor = 0;    
        for(int index = 0, len = lServer.size(); index < len - 1; index++)
        {    
            if(index ==0)
            {    
                divisor = greaterCommonDivisor(lServer[index].GetWeight(), lServer[index + 1].GetWeight());
                continue;
            }
          
            divisor = greaterCommonDivisor(divisor, lServer[index].GetWeight());   
        }    
        return divisor;    
    }  
      
   
     // 得到list中的最大的权重   
    int greatestWeight(std::vector<Server>& lServer)
    {    
        int weight = 0;    
        for(std::vector<Server>::iterator it = lServer.begin(); it!=lServer.end(); ++it)
        {    
            if(weight < it->GetWeight())
            {    
                weight = it->GetWeight();    
            }    
        }    
        return weight;    
    }  
      
     
     //*  算法流程：   
     //*  假设有一组服务器 S = {S0, S1, …, Sn-1}  
     //*  有相应的权重，变量currentIndex表示上次选择的服务器  
     //*  权值currentWeight初始化为0，currentIndex初始化为-1 ，当第一次的时候返回 权值取最大的那个服务器，  
    // *  通过权重的不断递减 寻找 适合的服务器返回 
     
     int GetServer(Server& s)
     {    
         while(true)
         {    
             m_iCurrentIndex = (m_iCurrentIndex + 1) % m_iSvrCount;    
             if(m_iCurrentIndex == 0)
             {    
                 m_iCurrentWeight = m_iCurrentWeight - m_iGcdWeight; 
                 
                 if(m_iCurrentWeight <= 0)
                 {    
                     m_iCurrentWeight = m_iMaxWeight;    
                     if(m_iCurrentWeight == 0)
                     {   
                         Show(); 
                         return -1;    
                     }    
                 }    
             }    
             
             if(m_lServer[m_iCurrentIndex].GetWeight() >= m_iCurrentWeight)
             {   
                Show(); 
                 s = m_lServer[m_iCurrentIndex];    
                 return 0;
             }    
         }    
     }   
       
     void init()
     {    
         m_lServer.push_back( Server("192.168.191.1", 1));    
         m_lServer.push_back( Server("192.168.191.2", 2));    
         m_lServer.push_back( Server("192.168.191.4", 4));    
         m_lServer.push_back( Server("192.168.191.8", 8));    
          
             
         m_iMaxWeight = greatestWeight(m_lServer);          //取最大权重
         m_iGcdWeight = greatestCommonDivisor(m_lServer);   //取最大公约数 
         m_iSvrCount = m_lServer.size();    

         printf("m_iCurrentIndex=%d;m_iCurrentWeight=%d;m_iMaxWeight=%d;m_iGcdWeight=%d;m_iSvrCount=%d;\n",
            m_iCurrentIndex,m_iCurrentWeight,m_iMaxWeight,m_iGcdWeight,m_iSvrCount);

     }    

};



int  main(int argc, char** argv)
{  

  WeightRoundRobin* weightRoundRobin = new WeightRoundRobin();    
  weightRoundRobin->init();    
      
  for(int i = 0; i < 15; i++)
  {    
      Server oServer("",0);
      int iRet = weightRoundRobin->GetServer(oServer);    
      printf("[%d]:server :[%s]; weight=%d\n",i, oServer.GetIp().c_str(),oServer.GetWeight());    
  }  
  delete weightRoundRobin;
//  printf("over!!\n");
  return 0;
}  










