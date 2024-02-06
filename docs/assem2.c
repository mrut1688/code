<<<<<<< HEAD
int main() {
    return absadd(-1,2);
    }

int absadd (int x, int y ){
    int t0=abs(x);
    int t1=abs(y);
    return t0+t1;

}

int abs (int v){

    int mask=v>>31;
    return (v+mask)-mask;
=======
int main() {
    return absadd(-1,2);
    }

int absadd (int x, int y ){
    int t0=abs(x);
    int t1=abs(y);
    return t0+t1;

}

int abs (int v){

    int mask=v>>31;
    return (v+mask)-mask;
>>>>>>> a73a13b226717f7103f548730cc403470029c9fc
}