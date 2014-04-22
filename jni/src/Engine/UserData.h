#ifndef _USERDATA_H_
    #define _USERDATA_H_

/**
 * Contains information to append it to Box2d objects.
 */
class UserData {
    public:
        int type;

    public:
        /**
         * Class constructor.
         */
        UserData(int type);
        int GetType();

};

#endif
