#ifndef RAID_H
#define RAID_H

#include "object.h"
#include "config.h"

#include <vector>

class Lun;

typedef std::vector<Lun> LunsList;

class Raid : public Object, private IConfig {
    public:
        Raid();
        virtual ~Raid();

        bool is_onlain();
        bool is_active();

    private:
        LunsList luns;
};

#endif // RAID_H
