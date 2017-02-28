/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

 namespace tools
 {
    class utils
    {
    public:
        static int CMID(int x, int min, int max)
        {
            return (x < min)? min : ((x > max)? max : x);
        }
    };
 }
