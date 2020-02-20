#ifndef CZY_MATH_FIT   
#define CZY_MATH_FIT   
#include <vector> 


namespace czy{  
    ///   
    /// \brief ��??�X?   
    ///   
   class Fit{  
        std::vector<double> factor; ///<?�X�Z����{�t?   
       double ssr;                 ///<�^?����M   
        double sse;                 ///<(�ѧE����M)   
       double rmse;                ///<RMSE�����?�t   
        std::vector<double> fitedYs;///<�s��?�X�Z��y�ȡA�b?�X?�i?�m?���O�s?��?�s   
    public:  
       Fit():ssr(0),sse(0),rmse(0){factor.resize(2,0);}  
       ~Fit(){}
	 void getFitedYs(std::vector<double>& fitedYs){fitedYs = this->fitedYs;}   
 template<typename T>  
        void polyfit(const std::vector<typename T>& y1  
            ,const std::vector<typename T>& y2  
            ,int poly_n  
            ,bool isSaveFitYs=true)  
        {  
            polyfit(&y1[0],&y2[0],getSeriesLength(y1,y2),poly_n,isSaveFitYs);  
        }  
        template<typename T>  
        void polyfit(const T* y1,const T* y2,size_t length,int poly_n,bool isSaveFitYs=true)  
        {  
           
		/*	factor.resize(poly_n+1,0);  
            int i,j;  
           //double *tempx,*tempy,*sumxx,*sumxy,*ata;   
            std::vector<double> tempx(length,1.0);  
  
            std::vector<double> tempy(y,y+length);  
  
            std::vector<double> sumxx(poly_n*2+1);  
            std::vector<double> ata((poly_n+1)*(poly_n+1));  
            std::vector<double> sumxy(poly_n+1);  
           for (i=0;i<2*poly_n+1;i++){  
                for (sumxx[i]=0,j=0;j<length;j++)  
                {  
                    sumxx[i]+=tempx[j];  
                    tempx[j]*=x[j];  
                }  
           }  
            for (i=0;i<poly_n+1;i++){  
                for (sumxy[i]=0,j=0;j<length;j++)  
                {  
                    sumxy[i]+=tempy[j];  
                    tempy[j]*=x[j];  
                }  
            }  
            for (i=0;i<poly_n+1;i++)  
                for (j=0;j<poly_n+1;j++)  
                    ata[i*(poly_n+1)+j]=sumxx[i+j];  
            gauss_solve(poly_n+1,ata,factor,sumxy);  */
            //?��?�X�Z��?�u�}?��?�t   
            fitedYs.reserve(length);  
        
			calcError(&y1[0],&y2[0],length,this->ssr,this->sse,this->rmse,isSaveFitYs);  
  	          //calcError(x,y,length,this->ssr,this->sse,this->rmse,isSaveFitYs);  
       // return true;
		
		}  

	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 double getSSE(){return sse;}  
        ///    
        /// \brief �^?����M   
        /// \return �^?����M   
        ///   
        double getSSR(){return ssr;}  
        ///    
        /// \brief �����?�t   
        /// \return �����?�t   
        ///   
        double getRMSE(){return rmse;}  
        ///    
        /// \brief �̩w�t?�A�t?�O0~1��?��?�A�O?�z�W�P�w?�Xɬ�ת��@?�q   
        /// \return �̩w�t?   
        ///   
        double getR_square(){return 1-(sse/(ssr+sse));}  
template <typename T>  
        static T Mean(const std::vector<T>& v)  
        {  
            return Mean(&v[0],v.size());  
        }  
        template <typename T>  
        static T Mean(const T* v,size_t length)  
        {  
            T total(0);  
            for (size_t i=0;i<length;++i)  
            {  
                total += v[i];  
            }  
            return (total / length);  
        }  

		template<typename T>  
        size_t getSeriesLength(const std::vector<typename T>& y1,const std::vector<typename T>& y2)  
        {  
            return (y1.size() > y2.size() ? y2.size() : y1.size());  
        }  


private:  
       template<typename T>  
     // typename T mean_y = Mean<T>(y,length);  
		   void calcError(const T* y1,const T* y2,size_t length,double& r_ssr,double& r_sse,double& r_rmse,bool isSaveFitYs=true)  
        {  
//           template<typename T>  
//	T mean_y = Mean<T>(y,length);
		   //	typedef typename T:: mean_y /*= Mean<T>(y,length)*/;	
		  T mean_y; 
			  mean_y = Mean(y2,length);  
            
		T yi(0);  
            fitedYs.reserve(length);  
            for (int i=0; i<length; ++i)  
            {  
                yi = y1[i];  
                r_ssr += ((yi-mean_y)*(yi-mean_y));//?��^?����M   
                r_sse += ((yi-y2[i])*(yi-y2[i]));//?�t����M   
                if (isSaveFitYs)  
                {  
                    fitedYs.push_back(double(yi));  
                }  
            }  
            r_rmse = sqrt(r_sse/(double(length)));  
        }  






	    
   
   
   
   
   
   
   
   
   
   
   
   
   };  
}  
  
  
#endif  