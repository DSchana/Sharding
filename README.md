# Sharding
File sharding

## Dependencies
 * OpenSSL

## Usage
`./deconstruct file-to-shard`

The sharded files are stored in a folder called `${file-to-shard}-shard`

`./reconstruct file-to-shard`

The shards from `${file-to-shard}-shard` are reconstructed into `${file-to-shard}` and compared to an expected file called `Original-${file-to-shard}`