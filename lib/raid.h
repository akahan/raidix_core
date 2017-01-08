#ifndef RAID_H
#define RAID_H

#include "object.h"
#include "config.h"

class Raid : public Object, private IConfig {
    public:
        Raid();
        virtual ~Raid();
};

#endif // RAID_H
