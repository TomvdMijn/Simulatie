#ifndef FILAMENTS_H_INCLUDED
#define FILAMENTS_H_INCLUDED

class filament{
    private:
        enum states{GROWING, SHRINKING, DEAD}
        int length;
        string state;

    public:
        filament(int len = 0, string sta = states[0]){
            length = len;
            state = sta;
        };


#endif // FILAMENTS_H_INCLUDED
