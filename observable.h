#pragma once

class Simulation;

/**
 * @brief Oberservable base class to filter a property of the current simulation.
 *        If you want to implement a custom observable inherit from this class.
 *        This can be for example the current properbility of the wave or the potential
 */
class Observable
{
public:
    /**
     * @brief The CheckTime enum The time when to filter the simulation
     */
    enum CheckTime {
        Startup   = (1 << 0), //! Filter at startup before the first solution gets computed.
        Iteration = (1 << 1), //! Filter at each iteration after the equation gets solved for a time step.
        Cooldown  = (1 << 2)  //! Filter after the simulation.
    };

    /**
     * @brief Observable
     * @param Time
     */
    Observable(CheckTime Time);

    /**
     * @brief #check Return true if the observable should filter at the given time.
     * @param currentTime The current time in the simulation.
     * @return true if the observable should filter at the current simulation time, otherwise false.
     */
    bool check(CheckTime currentTime);

    /**
     * @brief #filter Filter a property from the current simulation step.
     * @param sim The current simulation state.
     */
    virtual void filter(const Simulation& sim) = 0;

private:
    CheckTime time;
};
