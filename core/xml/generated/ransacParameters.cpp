/**
 * \file ransacParameters.cpp
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from stereoAlign.xml
 */

#include <vector>
#include <stddef.h>
#include "ransacParameters.h"

/**
 *  Looks extremely unsafe because it depends on the order of static initialization.
 *  Should check standard if this is ok
 *
 *  Also it's not clear why removing "= Reflection()" breaks the code;
 **/

namespace corecvs {
#if 0
template<>
Reflection BaseReflection<RansacParameters>::reflection = Reflection();
template<>
int BaseReflection<RansacParameters>::dummy = RansacParameters::staticInit();
#endif
} // namespace corecvs 

SUPPRESS_OFFSET_WARNING_BEGIN


using namespace corecvs;

int RansacParameters::staticInit(corecvs::Reflection *toFill)
{
    if (toFill == NULL || toFill->objectSize != 0) {
        SYNC_PRINT(("staticInit(): Contract Violation in <RansacParameters>\n"));
         return -1;
    }

    toFill->name = ReflectionNaming(
        "Ransac Parameters",
        "Ransac Parameters",
        ""
    );

     toFill->objectSize = sizeof(RansacParameters);
     

    IntField* field0 = new IntField
        (
          RansacParameters::ITERATIONS_NUMBER_ID,
          offsetof(RansacParameters, mIterationsNumber),
          1000,
          "Iterations Number",
          "Iterations Number",
          "Iterations Number",
          true,
         1,
         9999999,
         1
        );
    toFill->fields.push_back(field0);
    /*  */ 
    BoolField* field1 = new BoolField
        (
          RansacParameters::USE_MEDIAN_ID,
          offsetof(RansacParameters, mUseMedian),
          false,
          "Use Median",
          "Use Median",
          "Use Median"
        );
    field1->widgetHint=BaseField::CHECK_BOX;
    toFill->fields.push_back(field1);
    /*  */ 
    DoubleField* field2 = new DoubleField
        (
          RansacParameters::INLIERS_PERCENT_ID,
          offsetof(RansacParameters, mInliersPercent),
          98,
          "Inliers Percent",
          "Inliers Percent",
          "Inliers Percent",
          true,
         0,
         146,
         1
        );
    field2->widgetHint=BaseField::SPIN_BOX;
    field2->suffixHint="%";
    field2->precision=2;
    toFill->fields.push_back(field2);
    /*  */ 
    DoubleField* field3 = new DoubleField
        (
          RansacParameters::INLIER_THRESHOLD_ID,
          offsetof(RansacParameters, mInlierThreshold),
          1,
          "Inlier Threshold",
          "Inlier Threshold",
          "Inlier Threshold",
          true,
         -999999,
         999999,
         1
        );
    field3->widgetHint=BaseField::SPIN_BOX;
    field3->precision=5;
    toFill->fields.push_back(field3);
    /*  */ 
    ReflectionDirectory &directory = *ReflectionDirectoryHolder::getReflectionDirectory();
    directory[std::string("Ransac Parameters")]= toFill;
   return 0;
}
int RansacParameters::relinkCompositeFields()
{
   return 0;
}

SUPPRESS_OFFSET_WARNING_END


