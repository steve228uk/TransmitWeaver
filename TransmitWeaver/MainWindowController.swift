//
//  MainWindowController.swift
//  TransmitWeaver
//
//  Created by Stephen Radford on 16/02/2016.
//  Copyright © 2016 Cocoon Development Ltd. All rights reserved.
//

import Cocoa

class MainWindowController: NSWindowController {

    override func windowDidLoad() {
        super.windowDidLoad()
    
        window?.titlebarAppearsTransparent = true
        window?.movableByWindowBackground  = true
        window?.backgroundColor = NSColor.whiteColor()
    }

}
