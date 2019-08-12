#include <memory>

#include "optimizationAlgorithm.h"
#include "metaheuristic/firstImprovement.h"
#include "../statistic/statistic.h"
#include "../solution/solutionArray.h"
#include "../stoppingCriteria/stoppingCriteria.h"
#include "../problem/problem.h"
#include "../problem/oneMax.h"
#include "metaheuristic/operator/mutation/flipBit.h"
#include "metaheuristic/selection/selection.h"
#include "metaheuristic/selection/selection_maximization.h"
#include "../stoppingCriteria/criteriaBudget.h"

using TYPE_FITNESS = unsigned int;
using TYPE_CELL = bool;
using SOL = SolutionArray<TYPE_FITNESS, TYPE_CELL>;

unique_ptr<FirstImprovement<SOL, TYPE_FITNESS, TYPE_CELL>> create(std::mt19937 &mt_rand) {
    
    unique_ptr<Statistic<SOL>> _statistic = make_unique<Statistic<SOL>>(true);
    unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> _stoppingCriteria = make_unique<StoppingCriteria<SOL, TYPE_FITNESS>>();
    _stoppingCriteria->addCriteria(new CriteriaBudget<SOL, TYPE_FITNESS>(50));
    unique_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> _problem = make_unique<OneMax>(50);
    unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> _atomicOperation = make_unique<FlipBit<SOL, TYPE_FITNESS, TYPE_CELL>>(mt_rand, 1);
    unique_ptr<Selection<SOL>> _selection = make_unique<Selection_maximization<SOL>>();
    cout<<__FILE__<<" : "<<__LINE__<<endl;
    unique_ptr<FirstImprovement<SOL, TYPE_FITNESS, TYPE_CELL>> f = make_unique<FirstImprovement<SOL, TYPE_FITNESS, TYPE_CELL>>(mt_rand, move(_statistic), move(_stoppingCriteria), move(_problem), move(_atomicOperation), move(_selection));
    return move(f);
}

int main() {
    std::mt19937 mt_rand;
    SOL s(1,50);
    unique_ptr<FirstImprovement<SOL, TYPE_FITNESS, TYPE_CELL>> f= create(mt_rand);

    cout<<__FILE__<<" : "<<__LINE__<<endl;
    f->operator()(s);
    cout<<__FILE__<<" : "<<__LINE__<<endl;
    return 0;
}