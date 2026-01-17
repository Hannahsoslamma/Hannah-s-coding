#ifndef H_ConsumeItem
#define H_ConsumeItem

#include "Item.h"

class ConsumeItem : public Item {
private:
    vector<Effect*> consumeEffects;

public:
    ConsumeItem() {
        type = "consume";
    }
    
    void setActiveMessage(string s) {
        activeMessage = s;
    }

    string getActiveMessage() {
        return activeMessage;
    }

    void setActiveArea(int i) {
        activeArea = i;
    }

    int getActiveArea() {
        return activeArea;
    }

    void addEffect(Effect* temp) {
        consumeEffects.push_back(temp);
    }

    vector<Effect*> getItemConsumeEffects() {
        return consumeEffects;
    }

};

#endif
