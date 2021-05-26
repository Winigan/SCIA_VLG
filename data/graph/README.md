# Graphes

* [Bitcoin OTC trust weighted signed network](soc-sign-bitcoinotc.csv)
    * *Description:* This is who-trusts-whom network of people who trade using Bitcoin on a platform called Bitcoin OTC. Since Bitcoin users are anonymous, there is a need to maintain a record of users' reputation to prevent transactions with fraudulent and risky users. Members of Bitcoin OTC rate other members in a scale of -10 (total distrust) to +10 (total trust in steps of 1. This is the first explicit weighted signed directed network available for research.
    * *Nodes*: 5,881
    * *Edges*:	35,592
    * *Range of edge weight*: -10 to +10
    * *Percentage of positive edges*: 89%
    * [*Source*](https://snap.stanford.edu/data/soc-sign-bitcoin-otc.html) 
* [Gnutella peer-to-peer network, August 8 2002](p2p-Gnutella08.txt)
    * *Description:* A sequence of snapshots of the Gnutella peer-to-peer file sharing network from August 2002. There are total of 9 snapshots of Gnutella network collected in August 2002. Nodes represent hosts in the Gnutella network topology and edges represent connections between the Gnutella hosts.
    * *Nodes:* 6,301
    * *Edges:* 20,777
    * [*Source*](https://snap.stanford.edu/data/p2p-Gnutella08.html)
* [Wikipedia Requests for Adminship (with text)](wiki-RfA.txt)
    * *Description:* For a Wikipedia editor to become an administrator, a request for adminship (RfA) must be submitted, either by the candidate or by another community member. Subsequently, any Wikipedia member may cast a supporting, neutral, or opposing vote. This induces a directed, signed network in which nodes represent Wikipedia members and edges represent votes.
    * *Nodes:* 10,835
    * *Edges:* 159,388
    * [*Source*](https://snap.stanford.edu/data/wiki-RfA.html)