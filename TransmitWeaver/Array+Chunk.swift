//
//  Array+Chunk.swift
//  TransmitWeaver
//
//  Created by Stephen Radford on 16/02/2016.
//  http://stackoverflow.com/a/32999166/1087962
//

import Foundation

extension Array {
    func chunk(chunkSize : Int) -> Array<Array<Element>> {
        return 0.stride(to: self.count, by: chunkSize)
            .map { Array(self[$0..<$0.advancedBy(chunkSize, limit: self.count)]) }
    }
}