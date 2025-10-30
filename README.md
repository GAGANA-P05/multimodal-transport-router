# Smart Route Optimizer 🚌🚇🚶

A high-performance C implementation of Dijkstra's algorithm for finding the fastest route through a multi-modal transportation network.

## Features

- **Multi-modal Transport**: Supports bus, metro, and walking routes
- **Time-optimized Pathfinding**: Finds the fastest route based on ETA rather than just distance
- **Complex Network**: 20-node graph with multiple route options and intersections
- **Bidirectional Edges**: Realistic two-way travel simulation

## How It Works

The program uses a modified Dijkstra's algorithm that prioritizes **Estimated Time of Arrival (ETA)** over distance to find the optimal route between any two nodes in the transportation network.

## Compilation

```bash
gcc -o route_optimizer main.c -std=c11
```

## Usage

```bash
./route_optimizer
```

You'll be prompted to enter:

- Source node (0-19)
- Destination node (0-19)

The program will output:

- Fastest route path
- Total ETA in minutes
- Total distance
- Transport modes used

## Example Output

```
Enter the source node (0-19): 0
Enter the destination node (0-19): 19

Fastest route from node 0 to node 19:
    ETA: 67 minutes
    Total Distance: 45 units
Path: 0 -> (bus) -> 2 -> (metro) -> 5 -> (metro) -> 9 -> (bus) -> 13 -> (metro) -> 17
```

## Graph Structure

- **20 nodes** representing locations
- **47 edges** with multiple transport options
- Each edge includes: distance, ETA, and transport mode

## Future Enhancements

- [ ] Real-time traffic integration
- [ ] Cost optimization (fare calculation)
- [ ] GUI visualization
- [ ] Dynamic graph updates

## License

MIT
