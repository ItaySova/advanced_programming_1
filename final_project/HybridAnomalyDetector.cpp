/*
 * Authors: Tomer Schwartz, Itay sova
 */
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

void HybridAnomalyDetector::learnNormal(const TimeSeries &ts) {
    vector<string> atts=ts.gettAttributes();
    size_t len=ts.getRowSize();
    float vals[atts.size()][len];
    for(size_t i=0;i<atts.size();i++){
        for(size_t j=0;j<ts.getRowSize();j++){
            vals[i][j]=ts.getAttributeData(atts[i])[j];
        }
    }

    for(size_t i=0;i<atts.size();i++){

        string f1=atts[i];
        float max=0;
        size_t jmax=0;
        for(size_t j=i+1;j<atts.size();j++){

            float p=abs(pearson(vals[i],vals[j],len));
            if(p>max){
                max=p;

                jmax=j;
            }
        }

        string f2=atts[jmax];

        Point** ps=toPoints(ts.getAttributeData(f1),ts.getAttributeData(f2));

        if(max>threshold){
            size_t len=ts.getRowSize();
            correlatedFeatures c;
            c.feature1=f1;
            c.feature2=f2;
            c.corrlation=max;
            c.lin_reg=linear_reg(ps,len);
            c.threshold=findThreshold(ps,len,c.lin_reg)*1.1; // 10% increase
            c.isLinear=true;
            cf.push_back(c);
        }else if(max>0.5){
            size_t len=ts.getRowSize();
            correlatedFeatures c;
            c.feature1=f1;
            c.feature2=f2;
            c.corrlation=max;
            c.cir_reg= findMinCircle(ps,len);
            c.threshold=c.cir_reg.getRadius()*1.1; // 10% increase
            c.isLinear= false;
            cf.push_back(c);
        }

        // delete points
        for(size_t k=0;k<len;k++)
            delete ps[k];
        delete[] ps;
    }
}

vector<AnomalyReport> HybridAnomalyDetector::detect(const TimeSeries &ts) {
    /*
    vector<AnomalyReport> reports;
    for(auto & i : cf) { //for every corelation feature
        string description = i.feature1 + "-" + i.feature2;
        vector<float> ValuesF1 = ts.getAFeature(ts.getFeatureN(i.feature1));
        vector<float> ValuesF2 = ts.getAFeature(ts.getFeatureN(i.feature2));
        float currentDistance;
        if (i.isLinear) {

            //for every 2 features we check if their was a deviation
            for (int j = 0; j < ValuesF1.size(); j++) {

                currentDistance = dev(Point(ValuesF1.at(j), ValuesF2.at(j)), i.lin_reg);

                if (currentDistance > i.threshold) { //we report about the deviation if their is
                    reports.push_back(AnomalyReport(description, j + 1));
                }
            }
        }
        else{
            for (int j = 0; j < ValuesF1.size(); j++) {
                currentDistance = distance(i.cir_reg.getCenter(),Point(ValuesF1.at(j), ValuesF2.at(j)));
                if (currentDistance > i.threshold) { //we report about the deviation if their is
                    reports.push_back(AnomalyReport(description, j + 1));
                }
            }
        }
    }

    return reports;
     */
    vector<AnomalyReport> v;
    for_each(cf.begin(),cf.end(),[&v,&ts,this](correlatedFeatures c){
        vector<float> x=ts.getAttributeData(c.feature1);
        vector<float> y=ts.getAttributeData(c.feature2);
        string d = c.feature1 + "-" + c.feature2;
        if(c.isLinear) {
            for (size_t i = 0; i < x.size(); i++) {
                if (isAnomalous(x[i], y[i], c)) {
                    v.push_back(AnomalyReport(d, (i + 1)));
                }
            }
        }else{
            for (int j = 0; j < x.size(); j++) {
                float currentDistance = distance(c.cir_reg.getCenter(),Point(x[j], y[j]));
                if (currentDistance > c.threshold) { //we report about the deviation if their is
                    v.push_back(AnomalyReport(d, j + 1));
                }
            }
        }
    });
    return v;
}


HybridAnomalyDetector::~HybridAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

float HybridAnomalyDetector::distance(Point a, Point b) {
    float difX=a.x-b.x;
    float difY=a.y-b.y;
    return sqrt(pow(difX,2) + pow(difY,2));}

