//reupload for testing purposes
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <cmath>
using namespace std;

class Lod
{
private:
    int x = 0;
    int y = 0;
    int cilovy_bod_x = 0;
    int cilovy_bod_y = 0;

public:
    int rotace = 0;
    char smer;
    Lod(int x, int y, char smer, int cilovy_bod_x, int cilovy_bod_y)
    {
        this->x = x;
        this->y = y;
        this->cilovy_bod_x = cilovy_bod_x;
        this->cilovy_bod_y = cilovy_bod_y; 

    }

    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
    int getCilovy_bod_x(){
        return cilovy_bod_x;
    }
    int getCilovy_bod_y(){
        return cilovy_bod_y;
    }
    char getSmer(){
        return smer;
    }
    int getRotace(){
        return rotace;
    }
    void setX(int x){
        this->x = x; 
    }
    void setY(int y){
        this->y = y;
    }
    void setSmer(char c){
        this->smer = c;
    }
    
    void setCilovy_bod_x(int cilX){
        this->cilovy_bod_x = cilX;
    }
    void setCilovy_bod_y(int cilY){
        this->cilovy_bod_y = cilY;
    }
    void setRotace(int value){
        this->rotace += value;
    }

    void addRotation(char c, int value) {
        if (c == 'L') {
            setRotace(value);
        } else if (c == 'R') {
            setRotace(-value);
        }
        rotace = (rotace + 360) % 360;
    }
    
    void moveForward(int value){
        switch(rotace){
            case 0:
                addX(value);
                break;
            case 90:
                addY(value);
                break;
            case 180:
                addX(-value);
                break;
            case 270:
                addY(-value);
                break;
            default:
                cout << "unknown rotation " << endl;
                break;
        }
    }
    void waypointRotation(char action, int value){
        int placeholder = 0;
        
        switch (action)
        {
        case 'L':
            switch (value)
            {
            case 90:
                placeholder = getCilovy_bod_y();
                setCilovy_bod_y(getCilovy_bod_x());
                setCilovy_bod_x(-placeholder);
                break;
            case 180:
                setCilovy_bod_x(-getCilovy_bod_x());
                setCilovy_bod_y(-getCilovy_bod_y());
                break;
            case 270:
                placeholder = getCilovy_bod_y();
                setCilovy_bod_y(-getCilovy_bod_x());
                setCilovy_bod_x(placeholder);
                break;
            
            default:
                break;
            }
            break;
        
        case 'R':
            switch (value)
            {
            case 90:
                placeholder = getCilovy_bod_y();
                setCilovy_bod_y(-getCilovy_bod_x());
                setCilovy_bod_x(placeholder);
                break;
            case 180:
                setCilovy_bod_x(-getCilovy_bod_x());
                setCilovy_bod_y(-getCilovy_bod_y());
                break;
            case 270:
                placeholder = getCilovy_bod_y();
                setCilovy_bod_y(getCilovy_bod_x());
                setCilovy_bod_x(-placeholder);
                break;


            default:
                break;
            }
            break;
        
        default:
            cout << "Unsupported instruction" << endl;
            break;
        }

        // rotace = (rotace + 360) % 360;
        // cout << "Current rotation: " << getRotace();
    }

    void moveToWaypoint(int value){
        for(int i = 0; i < value; i++){
            addX(getCilovy_bod_x());
            addY(getCilovy_bod_y());
        }

    }

    void addX(int xVal){
        x += xVal;
    }

    void addY(int yVal){
        y += yVal;
    }

    void addCilovy_bod_x(int cilXVal){
        cilovy_bod_x += cilXVal;
    }

    void addCilovy_bod_y(int cilYVal){
        cilovy_bod_y += cilYVal;
    }

    int calculateManhattan(int x, int y){
        return sqrt(x*x) + sqrt(y*y);
    }

    int naviguj(std::string cesta_soubor, bool druhe_reseni)
    {
        fstream file;
        file.open(cesta_soubor, ios::in);
        if(file.is_open()){
            string line;
            int radky=0;
            int validni_zaznamy=0;
            if(!druhe_reseni){
                while(getline(file,line)){
                    radky++;
                //   cout << line << endl;
                    if(line.size()>0){
                        validni_zaznamy++;
                        int hodnota = stoi(line.substr(1, line.size()-1));
                        char action = line[0];
                        //cout << "smer je: "<<cumak << " a hodnota je: "<<hodnota << endl;
                        
                        switch (action){
                        case 'N':
                            cout << "Ship sails north. Instruction: ("<<line<<") Its current position is: "<< endl << "X: " << getX() << " Y: "<< getY() <<" Heading: " << getRotace() <<endl;
                            addY(hodnota);
                            cout << hodnota << endl;
                            break;
                        case 'W':
                            cout << "Ship sails west. Instruction: ("<<line<<") Its current position is: "<< endl << "X: " << getX() << " Y: "<< getY() <<" Heading: " << getRotace() << endl;
                            addX(-hodnota);
                            cout << hodnota << endl;
                            break;
                        case 'S':
                            cout << "Ship sails south. Instruction: ("<<line<<") Its current position is: "<< endl << "X: " << getX() << " Y: "<< getY() <<" Heading: " << getRotace() << endl;
                            addY(-hodnota);
                            cout << hodnota << endl;
                            break;
                        case 'E':
                            cout << "Ship sails east. Instruction: ("<<line<<") Its current position is: "<< endl << "X: " << getX() << " Y: "<< getY() <<" Heading: " << getRotace() << endl;
                            addX(hodnota);
                            cout << hodnota << endl;
                            break;
                        case 'L':
                            cout << "Ship rotates left. Instruction: ("<<line<<") Its current position is: "<< endl << "X: " << getX() << " Y: "<< getY() <<" Heading: " << getRotace() << endl;
                            addRotation(action,hodnota);
                            
                            break;
                        case 'R':
                            cout << "Ship rotates right. Instruction: ("<<line<<") Its current position is: "<< endl << "X: " << getX() << " Y: "<< getY() <<" Heading: " << getRotace() << endl;
                            addRotation(action,hodnota);
                            
                            break;
                        case 'F':
                            cout << "Ship sails forward. Instruction: ("<<line<<") Its current position is: "<< endl << "X: " << getX() << " Y: "<< getY() <<" Heading: " << getRotace() << endl;
                            moveForward(hodnota);
                            break;

                        default:
                            cout << "Ship sails somewhere " << endl;            
                            break;

                        }
                    }    
                }
            }else{
                while(getline(file,line)){
                    radky++;
                    if(line.size()>0){
                        validni_zaznamy++;
                        int hodnota = stoi(line.substr(1, line.size()-1));
                        char action = line[0];
                        switch (action){
                        case 'N':
                            cout << "Waypoint moves north. Instruction: ("<<line<<") Its current position is: "<< endl << "X: " << getCilovy_bod_x() << " Y: "<< getCilovy_bod_y() <<" Heading: " << getRotace() <<endl;
                            addCilovy_bod_y(hodnota);
                            cout << hodnota << endl;
                            break;
                        case 'W':
                            cout << "Waypoint moves west. Instruction: ("<<line<<") Its current position is: "<< endl << "X: " << getCilovy_bod_x() << " Y: "<< getCilovy_bod_y() <<" Heading: " << getRotace() << endl;
                            addCilovy_bod_x(-hodnota);
                            cout << hodnota << endl;
                            break;
                        case 'S':
                            cout << "Waypoint moves south. Instruction: ("<<line<<") Its current position is: "<< endl << getCilovy_bod_x() << " Y: "<< getCilovy_bod_y() <<" Heading: " << getRotace() << endl;
                            addCilovy_bod_y(-hodnota);
                            cout << hodnota << endl;
                            break;
                        case 'E':
                            cout << "Waypoint moves east. Instruction: ("<<line<<") Its current position is: "<< endl<< getCilovy_bod_x() << " Y: "<< getCilovy_bod_y() <<" Heading: " << getRotace() << endl;
                            addCilovy_bod_x(hodnota);
                            cout << hodnota << endl;
                            break;
                        case 'L':
                            cout << "Waypoint rotates left. Instruction: ("<<line<<") Its current position is: "<< endl<< getCilovy_bod_x() << " Y: "<< getCilovy_bod_y() <<" Heading: " << getRotace() << endl;
                            addRotation(action,hodnota);
                            waypointRotation(action,hodnota);
                            break;
                        case 'R':
                            cout << "Waypoint rotates right. Instruction: ("<<line<<") Its current position is: "<< endl << "X: "<< getCilovy_bod_x() << " Y: "<< getCilovy_bod_y() <<" Heading: " << getRotace() << endl;
                            addRotation(action,hodnota);
                            waypointRotation(action,hodnota);
                            break;
                        case 'F':
                            cout << "Ship sails forward. Instruction: ("<<line<<") Its current position is: "<< endl << "X: "<< getCilovy_bod_x() << " Y: "<< getCilovy_bod_y() <<" Heading: " << getRotace() << endl;
                            moveToWaypoint(hodnota);
                            break;

                        default:
                            break;
                        
                            cout << "Ship sails somewhere " << endl;            
                        
                        }
                    }    
                }
            
            }
        }
        // cout << "final values of X and Y"<<endl;
        // cout << "X: " <<getX()<< "Y: " << getY() << endl;
        // cout << "Manhattan distance is: " << calculateManhattan(getX(),getY());
        return calculateManhattan(getX(),getY());
        
    }
};

#ifndef __TEST__
int main()
{   

    Lod lod(0, 0, 'E', 10, 1);
    std::cout << lod.naviguj("vstup_1.txt", false) << std::endl;
    Lod lod2(0, 0, 'E', 10, 1);
    std::cout << lod2.naviguj("vstup_1.txt", true) << std::endl;
    return 0;
}
#endif // __TEST__
