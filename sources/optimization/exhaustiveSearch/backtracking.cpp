///
/// @file backtracking.hpp
/// @author Jxtopher
/// @version 1
/// @date 2020-10
///

#include <optimization/exhaustiveSearch/backtracking.h>

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
Backtraking<SOL, TYPE_FITNESS, TYPE_CELL>::Backtraking(
    std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
    std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
    std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem, Domain<TYPE_CELL> dom)
    : Optimization<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, std::move(statistic),
                                                 std::move(stoppingCriteria), problem),
      _dom(dom) {
    nbCall = 0;
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
Backtraking<SOL, TYPE_FITNESS, TYPE_CELL>::~Backtraking() {
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::unique_ptr<SOL> Backtraking<SOL, TYPE_FITNESS, TYPE_CELL>::operator()(const SOL& s) {
    return std::move(this->recursive(0, s.sizeArray(), s));
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::unique_ptr<SOL> Backtraking<SOL, TYPE_FITNESS, TYPE_CELL>::recursive(unsigned int currentCell,
                                                                          unsigned int depth,
                                                                          SOL s) {
    SOL new_s(currentCell + 1);
    if(currentCell > 0) {
        for(unsigned int i = 0; i < currentCell + 1; i++) { new_s(i, s(i)); }
    }

    unsigned int size_of_dom = _dom.get_size_domain(currentCell);
    for(unsigned int i = 0; i < size_of_dom; i++) {
        new_s(currentCell, _dom.pick(currentCell, i));
        if(currentCell + 1 < depth && this->_problem->evaluationSubSolution(new_s)) {
            std::unique_ptr<SOL> r = this->recursive(currentCell + 1, depth, new_s);
            if(r != nullptr) return std::move(r);
        } else if(currentCell + 1 == depth && this->_problem->evaluationSubSolution(new_s)) {
            // All good solutions
            // std::cout << __LINE__ << " " << new_s << std::endl;
            return std::move(std::make_unique<SOL>(new_s));
        }
    }
    return nullptr;
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::string Backtraking<SOL, TYPE_FITNESS, TYPE_CELL>::className() const {
    if(_class_name.empty())
        return "Backtraking";
    else
        return _class_name;
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void Backtraking<SOL, TYPE_FITNESS, TYPE_CELL>::className(const std::string& class_name) {
    _class_name = class_name;
}

template class Backtraking<Solution<double, double>, double, double>;
template class Backtraking<Solution<double, bool>, double, bool>;
template class Backtraking<Solution<int, bool>, int, bool>;
template class Backtraking<Solution<unsigned int, bool>, unsigned int, bool>;
template class Backtraking<Solution<double, unsigned int>, double, unsigned int>;
template class Backtraking<Solution<unsigned int, unsigned int>, unsigned int, unsigned int>;
} // namespace stocos