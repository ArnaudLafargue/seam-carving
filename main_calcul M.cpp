int min(int a, int b, int c){
    if (a<b){
        if (c<a){
            return c;
        }
        return a;
    }
    if (c<b){
        return c;
    }
    return a;
}


void calc_M(int[h*w] E, int[h*w] &M){
    for (int i=0; i<w; i++){
        M[i]=E[i];
    }
    for (int i=1; i<h;i++){
        for (int j=0; i<w; j++){
            M[i*w+j]=E[i*w+j] + min(M[(i-1)*w+j-1], M[(i-1)*w+j], M[(i-1)*w+j+1]);
        }
    }

}



int main()
{

    return 0;
}
