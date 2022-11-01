#pragma once

class Observer {
    public:
        virtual void occupy(int r, int c) = 0;
        virtual void evacuate(int r, int c) = 0;
        virtual bool is_walkable(int r, int c) = 0;
};