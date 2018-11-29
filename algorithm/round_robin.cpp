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
    int m_iCurrentIndex;   //**�ϴ�ѡ��ķ����� 
    
    int m_iCurrentWeight; //**��ǰ���ȵ�Ȩֵ     
    
    int m_iMaxWeight;   //**���Ȩ��    
    
    int m_iGcdWeight;   //**Ȩ�ص����Լ�� 
    
    int m_iSvrCount;  //**��������    
    
    std::vector<Server> m_lServer;   
      
public : 
    WeightRoundRobin():m_iCurrentIndex(-1),m_iCurrentWeight(0),m_iMaxWeight(0),m_iGcdWeight(0),m_iSvrCount(0)
        {}

    void Show()
    {
        printf("m_iCurrentIndex=%d;m_iCurrentWeight=%d;m_lServer[%d].GetWeight()=%d\n",
            m_iCurrentIndex,m_iCurrentWeight,m_iCurrentIndex,m_lServer[m_iCurrentIndex].GetWeight());
    }
    
     //* �õ���ֵ�����Լ��  
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
    

     //�õ�list������Ȩ�ص����Լ����ʵ����������ȡ���Լ��d��Ȼ��õ���d 
     //����һ��Ȩ��ȡ���Լ����ֱ��������      
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
      
   
     // �õ�list�е�����Ȩ��   
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
      
     
     //*  �㷨���̣�   
     //*  ������һ������� S = {S0, S1, ��, Sn-1}  
     //*  ����Ӧ��Ȩ�أ�����currentIndex��ʾ�ϴ�ѡ��ķ�����  
     //*  ȨֵcurrentWeight��ʼ��Ϊ0��currentIndex��ʼ��Ϊ-1 ������һ�ε�ʱ�򷵻� Ȩֵȡ�����Ǹ���������  
    // *  ͨ��Ȩ�صĲ��ϵݼ� Ѱ�� �ʺϵķ��������� 
     
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
          
             
         m_iMaxWeight = greatestWeight(m_lServer);          //ȡ���Ȩ��
         m_iGcdWeight = greatestCommonDivisor(m_lServer);   //ȡ���Լ�� 
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










