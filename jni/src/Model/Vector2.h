#ifndef _VECTOR2_H_
    #define _VECTOR2_H_
    /**
     * Models a 2D coordinate.
     */
    class Vector2 {
        public:
            /**
             * X coordinate.
             */
            float x;
            /**
             * Y coordinate.
             */
            float y;

        public:
            /**
             * Class constructor.
             */
            Vector2();
            /**
             * Class constructor.
             */
            Vector2(float x, float y);
            /**
             * Gets the eucledian distance between this and other vector.
             * @param vector Vector2 to get the distance to.
             * @return Distance to vector.
             */
            float Dist(Vector2* v);
            /**
             * Gets the eucledian squared distance between  this and other vector.
             * @param vector Vector2 to get the distance to.
             * @return Squared distance to vector.
             */
            float Dist2(Vector2* v);
            /**
             * Gets the angle for the vector.
             * @returns Angle for the vector.
             */
            float Angle();

    };
#endif
