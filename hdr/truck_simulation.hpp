class Truck_simulation 
{
public:
    Truck_simulation() { }
    virtual ~Truck_simulation() = default;
    Truck_simulation(const Truck_simulation &obj) = delete;
    Truck_simulation& operator=(const Truck_simulation&) = delete;
    Truck_simulation& operator=(Truck_simulation&&) = delete;
    friend std::ostream& operator<<(std::ostream& ostr, const Truck_simulation& obj) {
        return obj.output(ostr);
    }
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
  auto format(const Truck_simulation& sVal, std::format_context& context) const { 
    //return std::format_to(context.out(), "{}", sVal.getValue());
    return std::format_to(context.out(), "Truck_simulation:");
  }
};
