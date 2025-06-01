#pragma once
/**
   @file: transformer.h
   @breif: we shall make a transformer
*/
/*
    -->> key components of transformer
        .selfattention mechanism(to understand relationships between words)
        .multi-head attention(multiple SAM in parallel
        .feedforward neural network(simple dense layer in each transformer block
        .positional encoding(adds sequence indo to token embedding)
*/

/*  
    self-attention mechanism(SAM)
    -> calculates the relationship between each token in a sequence and every other token.
    .each word/token in a sentence is converted in three vectors
        :Query(Q) -> what this word is looking for.
        :Key(K)   -> what information this word has.
        :Value(V) -> the information itself.
    .for each pair of tokens, the model computes
                ATTENTION(Q,K,V) = softmax(q.k^t / sqrt(d_k) ) . V
            d_k is the dimension of the keys
*/

