#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;
int n,k=1;                  //total numer of enteries in
float sum_x=0;              //summation of independent variables
float sum_y=0;              //suumation of dependent variables
float sum_xsq=0;            //summation of X square
float sum_xy=0;             //summation of XY term
float sum_exp_var_Rsq=0;       //expected variation (numerator term for R square)
float sum_tot_var_Rsq=0;       //total variation (Denominator term for R square)
float sum_xtxm_mult_ytym=0;   //Cofficient of bcap in standard error equation
float sum_y_sub_ymean_sq=0;         //summation of (Y - ymean)^2
float sum_x_sub_xmean_sq=0;         //summation of (X - Xmean)^2
class Regression_Analysis
{
    float a,b,Ymean,Xmean,t,sb;        //a is vertical intercept,  b is slope
    float R2;                          // coefficient of determination
    float x[100];                      //array of independent variables
    float y[100];                      //array of dependent variables
    float x_square[100];               // array of x square Values
    float x_y[100];                    //array of XY values
    float y_tcap[100];                 // y_tcap
    float yt_sub_ymean[100];           //(y_tcap - ymean)
    float y_sub_ymean[100];            //(Y - Ymean)
    float xi_sub_xmean[100];           //(xi - xmean)
    float y_sub_ycap[100];             //(Y - Y cap)
    float x_sub_xmean[100];            //(X - Xmean)
    float r;                           //coefficient of correlation
    int bcap;                          // bcap
    float Se;                          //standard error
    public:
    void getdata();
    void algo();
    void display();
};
void Regression_Analysis::getdata()
{
    cout<<"\n   Enter the total number of independent variables (n) = ";
    cin>>n;
    cout<<"\n   Enter the "<<n<<" independent variables (X): ";
    for(int i=0;i<n;i++)
        cin>>x[i];
    cout<<"\n   Enter the "<<n<<" dependent variables (Y): ";
    for(int i=0;i<n;i++)
        cin>>y[i];
}
void Regression_Analysis::algo()
{
    getdata();
    for(int i=0;i<n;i++)
    {
        sum_x+=x[i];
        sum_y+=y[i];
        x_square[i]=x[i]*x[i];
        x_square[i]=floor(x_square[i]*100+0.5)/100;
        x_y[i]=x[i]*y[i];
        x_y[i]=floor(x_y[i]*100+0.5)/100;
        sum_xy+=x_y[i];
        sum_xsq+=x_square[i];
    }
    sum_xy=floor(sum_xy*100+0.5)/100;
    sum_xsq=floor(sum_xsq*100+0.5)/100;
    a=((sum_xy*sum_x)-(sum_xsq*sum_y))/((sum_x*sum_x)-(n*sum_xsq));
    a=floor(a*100+0.5)/100;
    b=((sum_y*sum_x)-(sum_xy*n))/((sum_x*sum_x)-(n*sum_xsq));
    b=floor(b*100+0.5)/100;
    if(b<0)
        bcap=-1;
    else
        bcap=1;
    Ymean=sum_y/n;
    Ymean=floor(Ymean*100+0.5)/100;
    Xmean=sum_x/n;
    Xmean=floor(Xmean*100+0.5)/100;
    for(int i=0;i<n;i++)
    {
        y_tcap[i]=a+(b*x[i]);
        y_tcap[i]=floor(y_tcap[i]*100+0.5)/100;
        yt_sub_ymean[i]=y_tcap[i]-Ymean;
        yt_sub_ymean[i]=floor(yt_sub_ymean[i]*100+0.5)/100;
        y_sub_ymean[i]=y[i]-Ymean;
        y_sub_ymean[i]=floor(y_sub_ymean[i]*100+0.5)/100;
        x_sub_xmean[i]=x[i]-Xmean;
        x_sub_xmean[i]=floor(x_sub_xmean[i]*100+0.5)/100;
        y_sub_ycap[i]=y[i]-y_tcap[i];
        y_sub_ycap[i]=floor(y_sub_ycap[i]*100+0.5)/100;
        sum_exp_var_Rsq+=yt_sub_ymean[i]*yt_sub_ymean[i];
        sum_tot_var_Rsq+=y_sub_ymean[i]*y_sub_ymean[i];
        sum_xtxm_mult_ytym+=x_sub_xmean[i]*y_sub_ymean[i];
        sum_x_sub_xmean_sq+=pow(x_sub_xmean[i],2);
        sum_y_sub_ymean_sq+=pow(y_sub_ycap[i],2);
    }
    sum_exp_var_Rsq=floor(sum_exp_var_Rsq*100+0.5)/100;
    sum_tot_var_Rsq=floor(sum_tot_var_Rsq*100+0.5)/100;
    sum_xtxm_mult_ytym=floor(sum_xtxm_mult_ytym*100+0.5)/100;
    sum_x_sub_xmean_sq=floor(sum_x_sub_xmean_sq*100+0.5)/100;
    sum_y_sub_ymean_sq=floor(sum_y_sub_ymean_sq*100+0.5)/100;
    R2=sum_exp_var_Rsq/sum_tot_var_Rsq;
    R2=floor(R2*1000+0.5)/1000;
    r=sqrt(R2);
    r=floor(r*1000+0.5)/1000;
    Se=sqrt(((sum_tot_var_Rsq)-(b*sum_xtxm_mult_ytym))/(n-k-1));
    Se=floor(Se*100+0.5)/100;
    sb=sqrt((sum_y_sub_ymean_sq)/((n-k-1)*(sum_x_sub_xmean_sq)));
    sb=floor(1000*sb +0.5)/1000;
    t=b/sb;
    t=floor(1000*t +0.5)/1000;
}
void Regression_Analysis::display()
{
    algo();
    cout<<"\n\n";
    cout<<setw(10)<<"Independent (X)"<<setw(15)<<"Dependent (Y)"<<setw(10)<<"X^2"<<setw(15)
        <<"XY"<<setw(15)<<"Ytcap"<<setw(15)<<"Ytcap - YMean"<<setw(15)<<"Yt - Ymean"
        <<setw(15)<<"X -Xmean"<<setw(15)<<"Y -  Ycap"<<"\n\n";
    for(int i=0;i<n;i++)
    {
        cout<<setw(10)<<x[i]<<setw(15)<<y[i]<<setw(15)<<x_square[i]<<setw(15)
        <<x_y[i]<<setw(15)<<y_tcap[i]<<setw(15)<<yt_sub_ymean[i]<<setw(15)<<y_sub_ymean[i]
        <<setw(15)<<x_sub_xmean[i]<<setw(15)<<y_sub_ycap[i]<<"\n";
    }
    cout<<"\n\n";
    cout<<setw(10)<<sum_x<<setw(15)<<sum_y<<setw(15)<<sum_xsq<<setw(15)
        <<sum_xy<<setw(15)<<"-"<<setw(15)<<"-"<<setw(15)<<"-"
        <<setw(15)<<"-"<<setw(15)<<"-"<<"\n";
    cout<<"\n\n";
    cout<<"     "<<n<<"a + "<<sum_x<<"b = "<<sum_y<<"    ........(1)\n\n";
    cout<<"     "<<sum_x<<"a + "<<sum_xsq<<"b = "<<sum_xy<<".......(2)\n\n";
    cout<<"     solving eq 1 and 2 we get,\n";
    cout<<"         a = "<<a<<"  & b = "<<b;
    cout<<"\n\n     regression line equation :  ";
    cout<<" Y = "<<a<<" + ("<<b<<")X\n";
    cout<<"\n     Ymean= "<<Ymean<<"   &&"<<"   Xmean = "<<Xmean;
    cout<<"\n\n     Expected variation = "<<sum_exp_var_Rsq;
    cout<<"\n\n     Total variation = "<<sum_tot_var_Rsq;
    cout<<"\n\n     Coefficient of determination (Rsquare) = "<<R2;
    cout<<"\n\n     Coefficient of correlation (r) = "<<r*bcap;
    cout<<"\n\n     Summation of ((X - Xmean)(Y-Ymean)) = "<<sum_xtxm_mult_ytym;
    cout<<"\n     Summation of (Y - Ycap)^2 = "<<sum_y_sub_ymean_sq;
    cout<<"\n     Summation of (X - Xmean)^2 = "<<sum_x_sub_xmean_sq;
    cout<<"\n\n     Standard error (Se)= "<<Se;
    cout<<"\n\n     value of sb = "<<sb;
    cout<<"\n\n     t value using formula (b/sb) = "<<t;
    cout<<"\n\n     :)\n\n";
}
int main()
{
    Regression_Analysis R1;
    R1.display();
    return 0;
}