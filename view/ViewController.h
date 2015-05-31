//
// Created by John Uiterwyk on 5/30/15.
//

#ifndef GENETICVISION_VIEWCONTROLLER_H
#define GENETICVISION_VIEWCONTROLLER_H

#include "../model/Model.h"


namespace GeneticVision {
    class ViewController {
    public:
        ViewController();

        void modelUpdated(GeneticVision::Model &model);

    };
}


#endif //GENETICVISION_VIEWCONTROLLER_H
