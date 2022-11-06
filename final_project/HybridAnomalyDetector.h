/*
 * Authors: Tomer Schwartz, Itay sova
 */

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();

    void learnNormal(const TimeSeries &ts) override;

    vector<AnomalyReport> detect(const TimeSeries &ts) override;
    float distance(Point a,Point b);
    void setCorrelationThreshold(float threshold){
        this->threshold=threshold;
    }

};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
