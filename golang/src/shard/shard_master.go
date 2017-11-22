package shard

import (
	"log"
	// "net/rpc"
	"strconv"
)

const MS_PER_ROUND = 1000

type ShardMaster struct {
	Shards    map[int]string
	MaxShards int
	CurrShard int
}

func (master ShardMaster) GetNextTarget() string {
	master.CurrShard = (master.CurrShard + 1) % master.MaxShards
	return master.Shards[master.CurrShard]
}

func NewShardMaster(shards map[int]string) ShardMaster {
	master := ShardMaster{shards, len(shards), 0}
	return master
}

func StartShardMaster(count int) ShardMaster {

	shards_locations := make(map[int]string)
	shards := make(map[int]Shard)

	for i := 0; i < count; i++ {
		port := strconv.Itoa(8081 + i)
		shards_locations[i] = "localhost:" + port
	}

	for k := range shards_locations {
		shards[k] = NewShard(shards_locations, k, MS_PER_ROUND, 8081+k)
		go StartShardHttp(shards[k])
	}

	return NewShardMaster(shards_locations)
}

func (master ShardMaster) AddValue(key string, value string) {

	log.Println("Calling a function.")
	log.Println(key)
	log.Println(value)
	// args := ProposalRequest{1, 2, master.Shards}
	// reply := ProposalResponse{false}

	// log.Println("Dialing shard %s", master.Shards[0])
	//
	// client, err := rpc.DialHTTP("tcp", master.Shards[0])
	// if err != nil {
	// 	log.Fatal("Dialing error:\n", err)
	//
	// }
	//
	// for i := 0; i < 5; i++ {
	// 	log.Println("Calling.")
	// 	err = client.Call("Shard.Propose", args, &reply)
	// 	if err != nil {
	// 		log.Fatal("Proposal error:\n", err)
	// 	}
	//
	// 	if reply.Success {
	// 		break
	// 	}
	// 	log.Println("Proposal failed, retrying.")
	// }
	//
	// client

}
