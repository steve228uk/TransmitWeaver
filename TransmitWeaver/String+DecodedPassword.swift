//
//  String+DecodedPassword.swift
//  TransmitWeaver
//
//  Created by Stephen Radford on 16/02/2016.
//  Copyright © 2016 Cocoon Development Ltd. All rights reserved.
//

import Foundation

extension String {
    
    /**
     Decode an "encrypted" Dreamweaver password
     
     - returns: The decrypted password
     */
    func decodePassword() -> String {
        var characters: [Character] = []
        for (index, char) in [Character](self.characters).chunk(2).enumerate() {
            let string = String(char)
            let code = Int(strtoul(string, nil, 16)) - index
            characters.append(Character(UnicodeScalar(code)))
        }
        
        return String(characters)
    }
    
}