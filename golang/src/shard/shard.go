package shard

// import "fmt"
import "net/rpc"
import "net/http"
import "net"
import "log"
import (
	"fmt"
	"strconv"
	"time"
)
import "shard/datastore"

//import "net/http"
// import "errors"

type Shard struct {
	Shards     map[int]string // Map of shard ID to string network loc.
	ShardId    int            // Current shard ID
	Round      int            // Current round
	MsPerRound int            // Period before round expires
	Port       int
	Data       datastore.Datastore
}

type Shardable interface {
	Propose(req *ProposalRequest, res *ProposalResponse) error
}

type Datastore interface {
	AddValue(req *AddValueRequest, res *AddValueResponse) error
	GetValue(req *GetValueRequest, res *GetValueResponse) error
}

type ProposalRequest struct {
	Round  int
	Master int
	Shards map[int]string
	Key    string
}

type ProposalResponse struct {
	Success bool
	Agree   bool
	Value   string
}

func (shard *Shard) Propose(req *ProposalRequest, res *ProposalResponse) error {
	fmt.Printf("Proposal recieved in shard %d\n", (*shard).ShardId)
	if (*shard).Round > (*req).Round {
		(*res).Success = false
		return nil
	}

	(*res).Success = true
	(*res).Value = (*shard).Data.Retrieve((*req).Key)

	return nil
}

type AddValueRequest struct {
	key   string
	value string
}

type AddValueResponse struct {
	err error
}

func (shard Shard) propose(req ProposalRequest) map[int]ProposalResponse {
	leader_responses := make(map[int]ProposalResponse)

	// In the future this should be threaded with callbacks.
	for id, addr := range shard.Shards {
		if id == shard.ShardId {
			continue
		}
		reply := ProposalResponse{false, false, ""}
		log.Println("Dialing shard %s", addr)

		client, err := rpc.DialHTTP("tcp", addr)
		if err != nil {
			log.Println("ERROR: Dialing error:\n", err)

		}

		for i := 0; i < 5; i++ {
			log.Println("Calling.")
			err = client.Call("Shard.Propose", req, &reply)
			if err != nil {
				log.Println("ERROR:Proposal error:\n", err)
				continue
			}

			if reply.Success {
				if reply.Agree {
					leader_responses[id] = reply
				}
				break
			}
			log.Println("Proposal failed, retrying.")
		}
	}
	return leader_responses
}

func (shard *Shard) AddValue(req *AddValueRequest, res *AddValueResponse) error {
	log.Println("Calling a function.")
	s := *shard
	preq := ProposalRequest{s.Round, s.ShardId, s.Shards, (*req).key}

	leader_responses :=shard.propose(preq)

	// Not enough responses, advance the round and recurse.
	if len(s.Shards)/2 < len(leader_responses) {
		(*shard).Round++
		// We might just want to return an error.
		return shard.AddValue(req, res)
	}

	// Push the values to the clients.

	// for id, res := range leader_responses {
	// 	err = client.Call("Shard.Propose", args, &reply)
	// 	if err != nil {
	// 		log.Error("Proposal error:\n", err)
	// 		continue
	// 	}
	// }

	return nil
}

type GetValueRequest struct {
	key string
}

type GetValueResponse struct {
	found bool
	value string
	err   error
}

func (shard *Shard) GetValue(req *AddValueRequest, res *AddValueResponse) error {
	return nil
}

// ProposeLeader

// Propose

func NewShard(shards map[int]string, shardId int, msPerRound int, port int) Shard {
	shard := Shard{shards, shardId, 0, msPerRound, port, datastore.NewDatastore()}
	return shard
}

func StartShard(shard Shard) {

	server := rpc.NewServer()
	server.RegisterName("Shard", &shard)
	log.Println("Starting shard on port: " + strconv.Itoa(shard.Port) + "\n")

	l, e := net.Listen("tcp", ":"+strconv.Itoa(shard.Port))
	if e != nil {
		log.Fatal("listen error:", e)
	}

	// This statement links rpc server to the socket, and allows rpc server to accept
	// rpc request coming from that socket.
	go server.Accept(l)
}

func StartShardHttp(shard Shard) {
	rpc.Register(&shard)
	rpc.HandleHTTP()
	l, e := net.Listen("tcp", ":"+strconv.Itoa(shard.Port))
	if e != nil {
		log.Fatal("listen error:", e)
	}
	go http.Serve(l, nil)
}


func  StartShardServer(shard Shard){
	shardMux := http.NewServeMux()
	shardMux.HandleFunc("/Propose", shard.Propose)
	server := &http.Server{
    Addr:    ":" + strconv.Itoa(shard.Port),
    Handler: myMux,
	}

go server.ListenAndServe()
}
func StartShardThreadedHttp(shard Shard) {
	rpc.Register(&shard)
	rpc.HandleHTTP()
	port := "localhost:"+strconv.Itoa(shard.Port)
	go http.ListenAndServe(l, nil)
}

func getShards(count int) map[int]Shard {

	shards_locations := make(map[int]string)
	shards := make(map[int]Shard)

	for i := 0; i < count; i++ {
		port := strconv.Itoa(8081 + i)
		shards_locations[i] = "localhost:" + port
	}

	for k := range shards_locations {
		shards[k] = NewShard(shards_locations, k, MS_PER_ROUND, 8081+k)
	}

	return shards
}

func TestPropose() {
	log.Println("Starting proposal test")
	shards := getShards(3)

		log.Println("Starting Shard 1")
	go StartShardHttp(shards[1])
		log.Println("Starting Shard 2")
	//go StartShardHttp(shards[2])

		log.Println("Sleeping")

	duration := time.Duration(5) * time.Second
	time.Sleep(duration)

	// s := shards[0]
	// req := ProposalRequest{s.Round, s.ShardId, s.Shards, "key"}
	// res := s.propose(req)
  //
	// log.Println(len(res))

}
