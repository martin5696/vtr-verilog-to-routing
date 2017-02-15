#ifndef VPR_SLACK_EVALUATOR
#define VPR_SLACK_EVALUATOR
#include <map>
#include "atom_netlist_fwd.h"
#include "DomainPair.h"
#include "timing_analyzers.hpp"
#include "vtr_vector_map.h"

class SetupSlackCrit {
    public: //Constructors
        SetupSlackCrit(const AtomNetlist& netlist, const AtomMap& netlist_map);

    public: //Accessors

        //Returns the worst (least) slack of connections through the specified pin
        float setup_pin_slack(AtomPinId pin) const;

        //Returns the worst (maximum) criticality of connections through the specified pin.
        //  Criticality (in [0., 1.]) represents how timing-critical something is, 
        //  0. is non-critical and 1. is most-critical.
        float setup_pin_criticality(AtomPinId pin) const;

    public: //Mutators
        void update_slacks_and_criticalities(const tatum::TimingGraph& timing_graph, const tatum::SetupTimingAnalyzer& analyzer);

    private: //Implementation

        void update_slacks(const tatum::SetupTimingAnalyzer& analyzer);

        void update_pin_slack(const AtomPinId pin, const tatum::SetupTimingAnalyzer& analyzer);

        void update_criticalities(const tatum::TimingGraph& timing_graph, const tatum::SetupTimingAnalyzer& analyzer);

        void update_pin_criticality(AtomPinId pin, 
                                    const tatum::SetupTimingAnalyzer& analyzer, 
                                    const std::map<DomainPair,float>& max_req, 
                                    const std::map<DomainPair,float>& worst_slack);

    private: //Data
        const AtomNetlist& netlist_;
        const AtomMap& netlist_map_;
        
        vtr::vector_map<AtomPinId, float> pin_slacks_;
        vtr::vector_map<AtomPinId, float> pin_criticalities_;
};

//TODO: implement a HoldSlackCrit class for hold analysis


#endif
