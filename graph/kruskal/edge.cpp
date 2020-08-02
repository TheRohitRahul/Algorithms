class Edge{
    private:
        int mvertice1;
        int mvertice2;
        int medge_weight;

    public:
        Edge(int vertice1, int vertice2, int edge_weight=0): mvertice1(vertice1), mvertice2(vertice2), medge_weight(edge_weight){

        } 
    
        int get_vertice1(){
            return this->mvertice1;
        }
        int get_vertice2(){
            return this->mvertice2;
        }
        int get_edge_weight(){
            return this->medge_weight;
        }
};