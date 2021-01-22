class Graph {
    constructor() {
        this.edges = {};
        this.nodes = [];
    }

    addNode(node) {
        this.nodes.push(node);
        this.edges[node] = [];
    }

    addEdge(node1, node2, weight = 1) {
        this.edges[node1].push({ node: node2, weight: weight });
        this.edges[node2].push({ node: node1, weight: weight });
    }
    V() {
        return this.nodes;
    }
}

export { Graph } 