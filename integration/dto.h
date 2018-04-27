#pragma once

#include "util/percentage.h"
#include "util/amount.h"

namespace integration {

/**
 * Identifies a {@link integration::Customer}.
 */
typedef int CustomerId;


/**
 * Represents a registered customer.
 */
class Customer {
    std::string name;
    util::Percentage discount;

public:
    /**
     * Creates a new instance.
     *
     * @param name Name of the customer.
     * @param discount The percentage discount the customer
     *                 is eligible for.
     */
    Customer(std::string name, util::Percentage discount)
        : name(name)
        , discount(discount)
    {}

    /**
     * Gets the discount percentages.
     *
     * @return The percentage discount the customer is eligible for.
     */
    const util::Percentage getDiscountPercentage() const
    {
        return {discount};
    }

    /**
     * Gets the name.
     *
     * @return The name of the customer.
     */
    const std::string getName() const
    {
        return name;
    }
};

/**
 * Identifies an item.
 */
typedef int ItemId;

/**
 * Represents an item that can be sold.
 */
class Item {
    std::string description;
    util::Amount price;

public:
    /**
     * Creates a new instance.
     *
     * @param description A string describing the item.
     * @param price The price of the item (excluding tax).
     */
    Item(std::string description, util::Amount price)
        : description(description)
        , price(price)
    {}

    /**
     * Creates a new instance.
     *
     * @param other Another item to copy.
     */
    Item(const Item& other)
        : description(other.description)
        , price(other.price)
    {}

    /**
     * Gets a string describing the item.
     *
     * @return a string describing the item.
     */
    const std::string& getDescription() const
    {
        return description;
    }

    /**
     * Gets the price of the item (excluding tax).
     *
     * @return The price.
     */
    const util::Amount& getPrice() const
    {
        return price;
    }
};


/**
 * Represents a set of sold items of the same type.
 */
class SoldItemRecord {
    ItemId itemId;
    Item item;
    int quantity;
    util::Amount totalPrice;

public:
    /**
     * Creates a new instance.
     *
     * @param itemId Identifies the items.
     * @param item Describes the items.
     * @param quantity The number of items.
     * @param totalPrice The total gross price of the items.
     */
    SoldItemRecord(ItemId itemId, Item item, int quantity, util::Amount totalPrice)
        : itemId(itemId)
        , item(item)
        , quantity(quantity)
        , totalPrice(totalPrice)
    {}

    /**
     * Gets an identifier for the items.
     *
     * @return An identifier for the items.
     */
    ItemId getItemId() const
    {
        return itemId;
    }

    /**
     * Gets a description of the items.
     *
     * @return A description of the items.
     */
    const Item& getItem() const
    {
        return item;
    }

    /**
     * Gets the number of items.
     *
     * @return The number of items.
     */
    int getQuantity() const
    {
        return quantity;
    }

    /**
     * Gets the total price.
     *
     * @return The total gross price of the items.
     */
    util::Amount getTotalPrice() const
    {
        return totalPrice;
    }

    /**
     * Compare two sets of sold items.
     *
     * @param other The record to compare to.
     * @return True if the <code>other</code> record has an identifier that
     *         compares greater than this instance's identifier.
     */
    bool operator<(const SoldItemRecord& other) const
    {
        return itemId < other.itemId;
    }
};

}
