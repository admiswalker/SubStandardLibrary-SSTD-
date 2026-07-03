namespace sstd{
    template<typename T>
    void _argstack(std::vector<T>& res_stack, T&& obj){
        res_stack.push_back(obj);
    }
    template<typename T, class Head, class... Tail>
    void _argstack(std::vector<T>& res_stack, Head&& head, Tail&&... tail){
        sstd::_argstack(res_stack, std::move(head));
        sstd::_argstack(res_stack, std::forward<Tail>(tail)...);
    }
    
    template<typename T, class... Args>
    void argstack(std::vector<T>& res_stack, Args... args){
        sstd::_argstack(res_stack, std::forward<Args>(args)...);
    }

    //---

    template<class... ResArgs, class T>
    void _argstack(const std::tuple<ResArgs...>& res_tuple_pV, T&& obj){
        std::vector<T>* res_pTbl = std::get<std::vector<T>*>(res_tuple_pV);
        res_pTbl->push_back(obj);
    }
    template<class... ResArgs, class Head, class... Tail>
    void _argstack(const std::tuple<ResArgs...>& res_tuple_pV, Head&& head, Tail&&... tail){
        sstd::_argstack(res_tuple_pV, std::move(head));
        sstd::_argstack(res_tuple_pV, std::forward<Tail>(tail)...);
    }
    
    template<class... ResArgs, class... Args>
    void argstack(const std::tuple<ResArgs...>& res_tuple_pV, Args... args){
        sstd::_argstack(res_tuple_pV, std::forward<Args>(args)...);
    }
}
