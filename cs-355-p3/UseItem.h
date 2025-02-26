#ifndef H_UseItem
#define H_UseItem

#include "Item.h"

class UseItem : public Item {
private:
    vector<Rule*> useRules;

public:
    UseItem() {
        type = "use";
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
    void addRule(Rule* temp) {
        useRules.push_back(temp);
    }

    vector<Rule*> getItemUseRules() {
        return useRules;
    }

};

#endif
