class Truck_simulation 
{
public:
    // TODO: complete, just to get tests compiling.
    Truck_simulation(int num_trucks, int num_stations, unsigned int seed = 42) {
        (void)num_stations;
        (void)num_trucks;
        (void)seed;
    }
    virtual ~Truck_simulation() = default;
    Truck_simulation(const Truck_simulation &obj) = delete;
    Truck_simulation& operator=(const Truck_simulation&) = delete;
    Truck_simulation& operator=(Truck_simulation&&) = delete;
    friend std::ostream& operator<<(std::ostream& ostr, const Truck_simulation& obj) {
        return obj.output(ostr);
    }
    // TODO: complete, stub to get tests compiling.
    void run() {}
protected:
    virtual std::ostream& output(std::ostream& ostr) const {
        ostr << "Truck_simulation:";
        return ostr;
    }

};
template<>
struct std::formatter<Truck_simulation> {
  constexpr auto parse(std::format_parse_context& context) {
    return context.begin();
  }
};
