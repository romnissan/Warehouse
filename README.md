# Warehouse Simulation

This C++ program simulates a warehouse environment where customers place orders, volunteers handle them, and the system performs various operations to manage and process orders.

## Program Overview

The Warehouse Simulation program is a command-line application that opens a warehouse, assigns volunteers and customers, processes orders, and performs various actions to manage the warehouse. The simulation is initiated by providing a configuration file that describes the initial state of the warehouse.
## Features

- **Warehouse Management:** Initializes a warehouse with customers and volunteers based on a config file.
- **Order Handling:** Supports placing, processing, and delivering orders.
- **Simulation Steps:** Advances the simulation by performing a step, handling order processing, and managing volunteers.
- **Customer and Volunteer Management:** Allows for adding new customers and volunteers during the simulation.
- **Status Printing:** Provides detailed information on the status of orders, customers, and volunteers.
- **Backup and Restore:** Supports backing up and restoring the warehouse state.

## Usage

Run the program with a configuration file:
```bash
./warehouse config.txt
```

Once the program starts, you can interact with it by entering various commands. The program will execute the commands and update the state of the warehouse accordingly.

## Classes

- **Warehouse:** Manages volunteers, customers, and orders. Handles the flow of the simulation.
- **Customer:** Represents different types of customers (Soldier, Civilian) with unique IDs and order limits.
- **Volunteer:** An abstract class for different types of volunteers (Collector, Driver). Volunteers handle orders based on their roles.
- **Order:** Represents an order made by a customer, with different statuses (Pending, Collecting, Delivering, Completed).
- **BaseAction:** An abstract class for various actions that can be performed in the warehouse.

## Actions

- **SimulateStep:** Advances the simulation by a specified number of steps.
- **AddOrder:** Adds a new order for a specific customer.
- **AddCustomer:** Adds a new customer to the warehouse.
- **PrintOrderStatus:** Prints the status of a specific order.
- **PrintCustomerStatus:** Prints the status of a specific customer.
- **PrintVolunteerStatus:** Prints the status of a specific volunteer.
- **PrintActionsLog:** Prints a log of all actions performed during the simulation.
- **Close:** Closes the warehouse and prints the status of all orders.
- **BackupWarehouse:** Backs up the current state of the warehouse.
- **RestoreWarehouse:** Restores the warehouse to the last backed-up state.

## Input File Format

The configuration file should contain the initial data for customers and volunteers in the following format:

### Customers:
```plaintext
customer <customer_name> <customer_type> <customer_distance> <max_orders>
```

### Volunteers:
```plaintext
volunteer <volunteer_name> <volunteer_role> <volunteer_coolDown>/<volunteer_maxDistance> <distance_per_step>(for drivers only) <volunteer_maxOrders>(optional)
```
