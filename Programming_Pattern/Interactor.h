#ifndef HEADER__FILE__INTERACTOR
#define HEADER__FILE__INTERACTOR

class Tissue;

template <typename Self>
struct Interactor
{
    template <typename T>
    void connect_to(T &other)
    {
        for (Tissue &from : *static_cast<Self *>(this))
        {
            for (Tissue &to : other)
            {
                from.out.push_back(&to);
                to.in.push_back(&from);
            }
        }
    }
};

#endif /* HEADER__FILE__INTERACTOR */
