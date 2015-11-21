#pragma once


/**
 * @brief Wave Base class for wave representations for custom wave functions inherit from this class
 */
template <typename T>
class Wave
{
public:
    /**
     * @brief Wave Default constructor does nothing
     */
    Wave() {
    }

    /**
     * @brief getDisplacement Return the displacement of an atom with the given index.
     *                        The index goes from 0 to the count of the atoms in the simulation.
     * @param index The index of the atom in the simulation
     * @return The displacement of the atom from its normal position
     */
    virtual T getDisplacement(unsigned int index) const = 0;
};
