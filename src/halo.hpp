namespace halo {

template<int N>
struct Port {
    static constexpr int number = N;
    static bool clockEnable;
};

struct Halo {
    static Port<1> portB;
    struct Pin {} pin0;
};

};  // namespaceh halo
