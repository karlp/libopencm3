# Karl Palsson, May2018
import datetime

import usb1

GZ_REQ_SET_PATTERN=1

def processReceivedData(transfer):
    print(transfer.getStatus())
    if transfer.getStatus() != usb1.TRANSFER_COMPLETED:
        # Transfer did not complete successfully, there is no data to read.
        # This example does not resubmit transfers on errors. You may want
        # to resubmit in some cases (timeout, ...).
        return
    data = transfer.getBuffer()[:transfer.getActualLength()]
    # Process data...
    print("got data of len", len(data), data)
    # Resubmit transfer once data is processed.  (this just makes it loop forever)
    #transfer.submit()

def write_interleaved(context, handle):
    transfer_list = []
    for i in range(100):
        transfer = handle.getTransfer()
        # FIXME - make alternating transfers for 0xaa and 0xbb
        data = [0xaa] * 64
        ep = 1
        if i % 2 == 0:
            data = [0xbb] * 64
            ep = 3
            print(transfer.setBulk(usb1.ENDPOINT_OUT | ep, data))
        print(transfer.setBulk(usb1.ENDPOINT_OUT | ep, data))
        transfer.submit()
        transfer_list.append(transfer)
    while any(x.isSubmitted() for x in transfer_list):
        try:
            context.handleEvents()
        except usb1.USBErrorInterrupted:
            print("inter")


def doreal_live(context, handle):
    # Build a list of transfer objects and submit them to prime the pump.
    transfer_list = []
    for _ in range(5):
        transfer = handle.getTransfer()
        transfer.setBulk(usb1.ENDPOINT_IN | 2, 64, callback=processReceivedData)
        transfer.submit()
        transfer_list.append(transfer)

    #self.dev.ctrl_transfer(uu.CTRL_TYPE_VENDOR | uu.CTRL_RECIPIENT_INTERFACE, GZ_REQ_SET_PATTERN, 1)
    # and then do a few more...
    transfer = handle.getTransfer()
    transfer.setControl(usb1.REQUEST_TYPE_VENDOR | usb1.RECIPIENT_INTERFACE, GZ_REQ_SET_PATTERN, 1, 0, 1)
    transfer.submit()
    transfer_list.append(transfer)

    for _ in range(5):
        transfer = handle.getTransfer()
        transfer.setBulk(usb1.ENDPOINT_IN | 2, 64, callback=processReceivedData)
        transfer.submit()
        transfer_list.append(transfer)

    # Loop as long as there is at least one submitted transfer.
    while any(x.isSubmitted() for x in transfer_list):
        try:
            context.handleEvents()
        except usb1.USBErrorInterrupted:
            print("inter")

def bulk_read_perf(context, handle):

    rxc = 0
    desired = 10 * 1024 * 1024
    per_transfer = 100*1024
    def tput(xc, te):
        return (xc / 1024 / max(1, te.seconds + te.microseconds /
                                1000000.0))
    def my_callback(xfer):
        #print(xfer.getStatus())
        if xfer.getStatus() != usb1.TRANSFER_COMPLETED:
            # Transfer did not complete successfully, there is no data to read.
            # This example does not resubmit transfers on errors. You may want
            # to resubmit in some cases (timeout, ...).
            raise RuntimeError("We don't allow errors in this sort of testing")
        nonlocal rxc
        nonlocal desired
        nonlocal per_transfer
        if xfer.getActualLength() != per_transfer:
            raise RuntimeError("didn't read what we expected!")
        rxc += xfer.getActualLength()
        if rxc < desired:
            xfer.submit()

        #data = xfer.getBuffer()[:xfer.getActualLength()]
        # Process data...
        #print("got data of len", len(data), data)

    transfer_list = []
    ts = datetime.datetime.now()
    for _ in range(10):
        transfer = handle.getTransfer()
        transfer.setBulk(usb1.ENDPOINT_IN | 2, per_transfer, callback=my_callback)
        transfer.submit()
        transfer_list.append(transfer)

    while any(x.isSubmitted() for x in transfer_list):
        try:
            context.handleEvents()
        except usb1.USBErrorInterrupted:
            print("inter")

    te = datetime.datetime.now() - ts
    print("read %s bytes in %s for %s kps" % (rxc, te, tput(rxc, te)))


def kk1():
    with usb1.USBContext() as context:
        handle = context.openByVendorIDAndProductID(
            0xcafe,
            0xcafe,
            skip_on_error=True,
        )
        if handle is None:
            print("didn't find any matching gadget0")
            # Device not present, or user is not allowed to access device.
        print("Found a device handle", handle)
        with handle.claimInterface(0):
            # Do stuff with endpoints on claimed interface.
            #doreal_live(context, handle)
            #bulk_read_perf(context, handle)
            write_interleaved(context, handle)


def main():
    with usb1.USBContext() as context:
        for device in context.getDeviceIterator(skip_on_error=True):
            print('ID %04x:%04x' % (device.getVendorID(), device.getProductID()), '->'.join(str(x) for x in ['Bus %03i' % (device.getBusNumber(), )] + device.getPortNumberList()), 'Device', device.getDeviceAddress())


if __name__ == '__main__':
    kk1()
