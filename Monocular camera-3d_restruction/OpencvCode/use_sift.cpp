    #include "opencv2/core/core.hpp"  
    #include "highgui.h"  
    #include "opencv2/imgproc/imgproc.hpp"  
    #include "opencv2/features2d/features2d.hpp"  
    #include "opencv2/nonfree/nonfree.hpp"  
    #include "opencv2/legacy/legacy.hpp"  
      
#include <iostream>
#include <fstream>

    using namespace cv;  
    using namespace std;  
      
    int main(int argc, char** argv)  
    {  
		ofstream fout("info_result.txt");
       //��ƥ�������ͼ������img1����img2��Ҳ����Ҫ��img1��ʶ���img2  
       Mat img1 = imread("paper01.png");  
       Mat img2 = imread("paper02.png");  
      
       SIFT sift1, sift2;  
      
       vector<KeyPoint> key_points1, key_points2;  
      
       Mat descriptors1, descriptors2, mascara;  
      
       sift1(img1,mascara,key_points1,descriptors1);  
       sift2(img2,mascara,key_points2,descriptors2);  
         
       //ʵ��������ƥ��������BruteForceMatcher  
       BruteForceMatcher<L2<float>> matcher;    
       //����ƥ��������  
       vector<DMatch>matches;    
       //ʵ��������֮���ƥ�䣬�õ�����matches  
       matcher.match(descriptors1,descriptors2,matches);  
      
       //��ȡ��ǰ30�����ƥ����  
       std::nth_element(matches.begin(),     //ƥ�������ӵĳ�ʼλ��  
           matches.begin()+29,     // ���������  
           matches.end());       // ����λ��  
       //�޳��������ƥ����  
       matches.erase(matches.begin()+30, matches.end());  
      
       namedWindow("SIFT_matches");    
       Mat img_matches;    
       //�����ͼ���л���ƥ����  
       drawMatches(img1,key_points1,         //��һ��ͼ�������������  
           img2,key_points2,      //�ڶ���ͼ�������������  
           matches,       //ƥ��������  
           img_matches,      //ƥ�����ͼ��  
           Scalar(255,255,255));     //�ð�ɫֱ����������ͼ���е�������  
	   for(int i=0;i<30;i++){
	   fout<<"kp1: "<<key_points1[matches[i].queryIdx].pt<<endl;
	   }
	   fout<<" --- "<<endl;
	   for(int i=0;i<30;i++){
		   fout<<"kp2: "<<key_points2[matches[i].trainIdx].pt<<endl;
	   }
	   
	   
	   fout.close();
       imshow("SIFT_matches",img_matches);    
       waitKey(0);  
      
       return 0;  
    }  